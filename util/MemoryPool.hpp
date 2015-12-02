#ifndef __re_util_resourcemanager_hpp_defined
#define __re_util_resourcemanager_hpp_defined

#include <vector>

#include "Lazy.hpp"

#include "../defines.hpp"
#include "../LogFile.hpp"

#include <functional>
#include <type_traits>

#ifdef RE_DEBUG
	#define RE_INSPECT_HANDLES
#endif

#ifdef RE_INSPECT_HANDLES
#define _RE_HANDLE_INSPECT_MEMBER_DECL protected: T* _inspect; public:
#define _RE_HANDLE_INSPECT_UPDATE _inspect = this->operator T*();
#else
#define _RE_HANDLE_INSPECT_MEMBER_DECL
#define _RE_HANDLE_INSPECT_UPDATE
#endif

namespace re
{
	namespace util
	{

		template<class T>
		class MemoryPool;
		template<class T>
		class strong_handle;
		template<class T>
		class unique_handle;
		template<class T>
		class weak_handle;

		template<class T, class ...Args>
		REINL unique_handle<T> alloc(Args&&... args)
		{
			return MemoryPool<T>::GetInst()->alloc(std::forward<Args>(args)...);
		}
		
		template<class T, class U>
		REINL strong_handle<T> dynamic(const strong_handle<U> &handle)
		{
			return handle.dynamic_handle_cast<T>();
		}

		template<class T, class U>
		REINL strong_handle<T> cast(const strong_handle<U> &handle)
		{
			return handle.static_handle_cast<T>();
		}
	
		template<class T, class U>
		REINL weak_handle<T> dynamic(const weak_handle<U> &handle)
		{
			return handle.dynamic_handle_cast<T>();
		}

		template<class T, class U>
		REINL weak_handle<T> cast(const weak_handle<U> &handle)
		{
			return handle.static_handle_cast<T>();
		}

		template<class T>
		/*A MemoryPool for a specific Type. Allows relative pointers to elements rather than absolute pointers.*/
		class MemoryPool : public Singleton<MemoryPool<T>>
		{	friend class strong_handle<T>;
			friend class strong_handle<const T>;
			friend class unique_handle<T>;
			friend class unique_handle<const T>;
			friend class weak_handle<T>;
			friend class weak_handle<const T>;

			struct Entry
			{
				Entry() : usecount(0), nextFree(-1), object() { }
				Entry(Entry &&move) : usecount(move.usecount), nextFree(move.nextFree) {
					if(move.usecount)
					// if object was allocated, move it.
						( new (&object) T(std::move(*&move.object)) );
				}

				lazy<T> object;
				size_t nextFree;
				size_t usecount;
			};		


#define ENTRYAT(offset) (*reinterpret_cast<Entry*>(reinterpret_cast<byte*>(data.data())+offset))


			size_t firstFree;
			
			/*Contains whether an object is free or not.*/
			std::vector<Entry> data;

			REINL void inc_ref(size_t offset)
			{
				RE_ASSERT(offset % type_size == 0);
				RE_ASSERT(offset/type_size < data.size());
				RE_ASSERT(ENTRYAT(offset).usecount != 0);

				ENTRYAT(offset).usecount++;
			}

			REINL void dec_ref(size_t offset)
			{
				RE_ASSERT(offset/type_size < data.size());
				RE_ASSERT(ENTRYAT(offset).usecount != 0);

				if(!--ENTRYAT(offset).usecount)
					free(offset / type_size);
			}
#undef ENTRYAT

			static void destruct(T* obj)
			{
				obj->~T();
			}

		public:

			MemoryPool(): data(0), firstFree(-1), type_size(sizeof(Entry)), destructor(&destruct) {}
			MemoryPool(size_t capacity): data(0), firstFree(-1), type_size(sizeof(Entry)), destructor(&destruct) { reservePool(capacity); }

			void (*destructor)(T*);
			const size_t type_size;

			void for_each_s(std::function<void (const strong_handle<T> &obj)> fn)
			{
				for(size_t i = 0; i < data.size(); i++)
					if(data[i].usecount)
					{
						fn(strong_handle<T>(*this, i*type_size));
					}
			}
			void for_each_w(std::function<void (const weak_handle<T> &obj)> fn)
			{
				for(size_t i = 0; i < data.size(); i++)
					if(data[i].usecount)
						fn(weak_handle<T>(*this, i*type_size));
			}

			REINL T* get(size_t byte_offset)
			{
				// checks whether addressed object starts at a valid T[] index
				RE_ASSERT(byte_offset/type_size<data.size());
				RE_ASSERT(byte_offset % type_size == 0);

				// returns address of object with byte offset
				return reinterpret_cast<T*>(reinterpret_cast<byte*>(data.data())+byte_offset);
			}


			/*Deletes all objects and frees the pooled memory.*/
			void clear()
			{
				for(size_t i = 0; i<data.size())
					destructor(&data[i].object);
				data.clear();
			}

			inline size_t use_count(size_t offset)
			{
				RE_ASSERT(offset % type_size == 0);
				RE_ASSERT(offset / type_size < data.size());

				return data[offset / type_size].usecount;
			}

			void free(size_t index)
			{
				RE_ASSERT(index < data.size());
				RE_ASSERT(data[index].usecount == 0);

				// destroy object
				destructor(&data[index].object);

				if(firstFree > index)
				{
					data[index].nextFree = firstFree;
					firstFree = index;
				}
				else
				{
					for(size_t i = index; i-->0;)
						if((data[i].usecount == 0))
						{
							data[index].nextFree = data[i].nextFree;
							data[i].nextFree = index;
							break;
						}
				}
			}

			void reservePool(size_t size) { data.reserve(size); }
			void resizePool(size_t size)
			{
				for(size_t index = size; index<data.size(); i++)
					free(index);
				size_t oldSize = data.size();
				data.resize(size);
				if(oldSize)
					data[oldSize-1].nextFree = oldSize;
				for(size_t i = oldSize; i<data.size(); i++)
				{
					data[i].nextFree = i+1;
					data[i].usecount = 0;
				}
			}
			template<class ...Args>
			/*Returns a pointer to be used with placement new.*/
			unique_handle<T> alloc(Args&&... args)
			{
				if(firstFree == -1)
				{
					data.push_back(Entry());
					data.back().usecount = 1;
					unique_handle<T> ret(*this,(data.size()-1)*type_size);
					data.back().usecount--;
					new (ret) T(std::forward<Args>(args)...);
					return ret;
				}
				else
				{
					size_t index = firstFree;
					firstFree = data[firstFree].nextFree;

					data[index].usecount = 1;
					unique_handle<T> ret(*this, index*type_size);
					data[index].usecount--;
					new (ret) T(std::forward<Args>(args)...);
					return ret;
				}
			}

			size_t size() const { return data.size(); }
		};

		template<class T>
		/*A relative offset Pointer for elements inside MemoryPools.
		strong_handle affects the use count of the pool.*/
		class strong_handle
		{	friend class MemoryPool<T>;
			friend class weak_handle<T>;
			friend class weak_handle<const T>;

			MemoryPool<T> *pool;
			size_t byte_offset;

			_RE_HANDLE_INSPECT_MEMBER_DECL

			strong_handle(MemoryPool<T> &pool, unsigned byte_offset) : pool(&pool), byte_offset(byte_offset) { pool.inc_ref(byte_offset); }
			
		public:
			strong_handle() : pool(nullptr), byte_offset(-1) { _RE_HANDLE_INSPECT_UPDATE }
			strong_handle(nullptr_t) : pool(nullptr), byte_offset(-1) { _RE_HANDLE_INSPECT_UPDATE }

			strong_handle(const strong_handle<T> &copy) : pool(copy.pool), byte_offset(copy.byte_offset) { if(pool)pool->inc_ref(byte_offset); _RE_HANDLE_INSPECT_UPDATE }
			strong_handle(unique_handle<T> &&move) : pool(move.pool), byte_offset(move.byte_offset) { move.byte_offset = -1; _RE_HANDLE_INSPECT_UPDATE }
			~strong_handle() { if(valid()) pool->dec_ref(byte_offset); pool = nullptr; byte_offset = -1; _RE_HANDLE_INSPECT_UPDATE }
			strong_handle<T> &operator=(const strong_handle<T> &copy)
			{
				if(pool == copy.pool && byte_offset == copy.byte_offset)
					return *this;

				if(copy.valid())
					copy.pool->inc_ref(copy.byte_offset);
				if(valid())
					pool->dec_ref(byte_offset);

				pool = copy.pool;
				byte_offset = copy.byte_offset;
				_RE_HANDLE_INSPECT_UPDATE
				return *this;
			}
			strong_handle<T> &operator=(strong_handle<T> &&move)
			{
				if(&move == this)
					return *this;

				pool = move.pool;
				byte_offset = move.byte_offset;

				_RE_HANDLE_INSPECT_UPDATE

				move.pool = nullptr;
				move.byte_offset = -1;

				return *this;
			}

			REINL bool operator!=(const strong_handle<T> &other) const { return pool != other.pool || byte_offset != other.byte_offset; }
			REINL bool operator==(const strong_handle<T> &other) const { return pool == other.pool && byte_offset == other.byte_offset; }


			REINL operator bool() const { return valid(); }
			REINL bool valid() const { return byte_offset != -1 && pool != nullptr; }

			REINL size_t use_count() const { return valid()?pool->use_count(byte_offset) : 0; }

			REINL T& operator*() const { return *get(); }
			REINL T* get() const { return (valid())? pool->get(byte_offset) : nullptr; }
			REINL T* operator->() const { return (valid())? pool->get(byte_offset) : nullptr; }

			REINL operator T*() const { return get(); }

			template<class U>
			REINL strong_handle<U> static_handle_cast() const
			{
				static_assert(std::is_convertible<T*,U*>::value, "Bad static cast.");
				if(U* ptr = static_cast<U*>(get()))
					return strong_handle<U>(reinterpret_cast<MemoryPool<U>&>(*pool),
					reinterpret_cast<const byte*>(ptr) - reinterpret_cast<const byte*>(pool->data.data()));
				else return nullptr;
			}

			template<class U>
			REINL strong_handle<U> dynamic_handle_cast() const
			{
				if(U* ptr = dynamic_cast<U*>(get()))
					return strong_handle<U>(reinterpret_cast<MemoryPool<U>&>(*pool),
					reinterpret_cast<const byte*>(ptr) - reinterpret_cast<const byte*>(pool->data.data()));
				else
					return nullptr;
			}

		};

		template<class T>
		/*A possessive relative offset Pointer for elements inside MemoryPools.
		unique_handle affects the use count of the pool.
		Only one unique_handle can point to the same object at the same time.
		@note:
			If a unique_handle is assigned to another handle that affects the reference
			counting of the stored object, it is reset.*/
		class unique_handle
		{	friend class MemoryPool<T>;
			friend class strong_handle<T>;
			friend class weak_handle<T>;

			MemoryPool<T> *pool;
			size_t byte_offset;

			_RE_HANDLE_INSPECT_MEMBER_DECL

			unique_handle(MemoryPool<T> &pool, unsigned byte_offset) : pool(&pool), byte_offset(byte_offset) { pool.inc_ref(byte_offset); _RE_HANDLE_INSPECT_UPDATE }
		public:
			unique_handle() : pool(nullptr), byte_offset(-1) { _RE_HANDLE_INSPECT_UPDATE }
			unique_handle(nullptr_t) : pool(nullptr), byte_offset(-1) { _RE_HANDLE_INSPECT_UPDATE }
			unique_handle(unique_handle<T> &&move): pool(move.pool), byte_offset(move.byte_offset) { move.byte_offset = -1; _RE_HANDLE_INSPECT_UPDATE }
			~unique_handle() { if(valid()) pool->dec_ref(byte_offset); pool = nullptr; byte_offset = -1; _RE_HANDLE_INSPECT_UPDATE }

			unique_handle(const unique_handle<T> &copy) = delete;
			unique_handle<T> &operator=(const unique_handle<T> &copy) = delete;
			
			unique_handle<T> &operator=(unique_handle<T> &&move)
			{
				if(this == &move)
					return *this;

				if(valid())
					pool->dec_ref(byte_offset);

				pool = move.pool;
				byte_offset = move.byte_offset;
				
				move.byte_offset = -1;
				_RE_HANDLE_INSPECT_UPDATE
				return *this;
			}

			REINL bool operator!=(const strong_handle<T> &other) const { return pool != other.pool || byte_offset != other.byte_offset; }
			REINL bool operator==(const strong_handle<T> &other) const { return pool == other.pool && byte_offset == other.byte_offset; }

			
			REINL operator bool() const { return valid(); }
			REINL bool valid() const { return byte_offset != -1 && pool != nullptr; }

			REINL size_t use_count() const { return valid()?pool->use_count(byte_offset) : 0; }

			REINL T& operator*() const { return *get(); }
			REINL T* get() const { return (valid())? pool->get(byte_offset) : nullptr; }
			REINL T* operator->() const { return (valid())? pool->get(byte_offset) : nullptr; }

			REINL operator T*() const { return get(); }
		};

		template<class T>
		/*A relative offset Pointer for elements inside MemoryPools.
		weak_handle does not affect the use count of the pool.*/
		class weak_handle
		{	friend class MemoryPool<T>;

			MemoryPool<T> *pool;
			size_t byte_offset;

			_RE_HANDLE_INSPECT_MEMBER_DECL

			weak_handle(MemoryPool<T> &pool, unsigned index) : pool(&pool), byte_offset(index) { _RE_HANDLE_INSPECT_UPDATE }
		public:
			weak_handle() : pool(nullptr), byte_offset(-1) { _RE_HANDLE_INSPECT_UPDATE }
			weak_handle(nullptr_t) : pool(nullptr), byte_offset(-1) { _RE_HANDLE_INSPECT_UPDATE }
			~weak_handle() { pool = nullptr; byte_offset = -1; _RE_HANDLE_INSPECT_UPDATE }

			weak_handle(const strong_handle<T> &other) : pool(other.pool), byte_offset(other.byte_offset) { _RE_HANDLE_INSPECT_UPDATE }
			weak_handle(const unique_handle<T> &other) : pool(other.pool), byte_offset(other.byte_offset) { _RE_HANDLE_INSPECT_UPDATE }
			
			
			template<class U>
			REINL weak_handle<U> static_handle_cast() const
			{
				static_assert(std::is_convertible<T*,U*>::value, "Bad static cast.");
				if(U* ptr = static_cast<U*>(get()))
					return weak_handle<U>(reinterpret_cast<MemoryPool<U>&>(*pool),
					// offset.
					reinterpret_cast<const byte*>(ptr) - reinterpret_cast<const byte*>(pool->data.data()));
				else return nullptr;
			}

			template<class U>
			REINL weak_handle<U> dynamic_handle_cast() const
			{
				if(U* ptr = dynamic_cast<U*>(get()))
					return weak_handle<U>(reinterpret_cast<MemoryPool<U>&>(*pool),
					// offset.
					reinterpret_cast<const byte*>(ptr) - reinterpret_cast<const byte*>(pool->data.data()));
				else
					return nullptr;
			}


			REINL bool operator!=(const strong_handle<T> &other) const { return pool != other.pool || byte_offset != other.byte_offset; }
			REINL bool operator==(const strong_handle<T> &other) const { return pool == other.pool && byte_offset == other.byte_offset; }
			
			REINL operator bool() const { return valid(); }
			REINL bool valid() const { return byte_offset != -1 && pool != nullptr; }

			REINL size_t use_count() const { return valid()?pool->use_count(byte_offset) : 0; }

			REINL T& operator*() const { return *get(); }
			REINL T* get() const { return (valid())? pool->get(byte_offset) : nullptr; }
			REINL T* operator->() const { return (valid())? pool->get(byte_offset) : nullptr; }

			REINL operator T*() const { return get(); }
		};
	}
}

#endif