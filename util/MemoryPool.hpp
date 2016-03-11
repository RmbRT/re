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
		REINL unique_handle<T> alloc(Args&&... args);
		
		template<class T, class U>
		REINL strong_handle<T> dynamic(const strong_handle<U> &handle);

		template<class T, class U>
		REINL strong_handle<T> cast(const strong_handle<U> &handle);
	
		template<class T, class U>
		REINL weak_handle<T> dynamic(const weak_handle<U> &handle);

		template<class T, class U>
		REINL weak_handle<T> cast(const weak_handle<U> &handle);

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
				Entry();
				Entry(Entry &&move);

				size_t nextFree;
				size_t usecount;
				lazy<T> object;
			};

			size_t firstFree;
			size_t last_allocated_object_after; // the first address after the end of the last allocated object.

			/*Contains whether an object is free or not.*/
			std::vector<Entry> data;

			REINL void inc_ref(size_t byte_offset_entry);
			REINL void dec_ref(size_t byte_offset_entry);

			static void destruct(T* obj)
			{
				obj->~T();
			}

		public:

			MemoryPool();
			MemoryPool(size_t capacity);

			void (*const destructor)(T*);
			const size_t entry_size;

			/*For each function that passes a strong_handle of every object to the given function.
			@param[in] fn: a function that is called for every object allocated in this memory pool (using a strong_handle).*/
			void for_each_s(std::function<void (const strong_handle<T> &obj)> fn)
			{
				for(size_t i = 0; i < data.size(); i++)
					if(data[i].usecount)
					{
						fn(strong_handle<T>(*this, i*type_size));
					}
			}
			
			/*For each function that passes a weak_handle of every object to the given function.
			@param[in] fn: a function that is called for every object allocated in this memory pool (using a weak_handle).*/
			void for_each_w(std::function<void (const weak_handle<T> &obj)> fn)
			{
				for(size_t i = 0; i < data.size(); i++)
					if(data[i].usecount)
						fn(weak_handle<T>(*this, i*type_size));
			}

			REINL T* get(size_t byte_offset_entry, size_t byte_offset_object)
			{
				// checks whether addressed object starts at a valid T[] index
				RE_DBG_ASSERT(byte_offset_entry < last_allocated_object_after);
				RE_DBG_ASSERT(byte_offset_entry % type_size == 0);
				RE_DBG_ASSERT(byte_offset_object < entry_size);

				// returns address of object with byte offset
				return reinterpret_cast<T*>(reinterpret_cast<byte*>(data.data())+byte_offset_entry+byte_offset_object);
			}


			/*Deletes all objects and frees the pooled memory.*/
			void clear()
			{
				for(size_t i = 0; i<data.size())
					destructor(&data[i].object);
				data.clear();
			}

			/*Returns how many strong_handles or unique_handles are referring to the entry at the given relative address.
			@param[in] byte_offset_entry: the relative address of the Entry structure in the pool.*/
			inline size_t use_count(size_t byte_offset_entry)
			{
				RE_DBG_ASSERT(offset % type_size == 0);
				RE_DBG_ASSERT(byte_offset < last_allocated_object_after);

				return reinterpret_cast<Entry*>(reinterpret_cast<byte*>(data.data()) + byte_offset_entry)->usecount;
			}

			/*Destroys the object allocated at the given byte offset in the pool.
			@param[in] byte_offset_entry:
				the relative address of the Entry that contains the instance to be destroyed in the pool.*/
			void free(size_t byte_offset_entry)
			{

				RE_DBG_ASSERT(byte_offset_entry % entry_size == 0);
				RE_DBG_ASSERT(byte_offset_entry < last_allocated_object_after);
				
				Entry * const entry = reinterpret_cast<Entry*>(reinterpret_cast<byte*>(data.data())+byte_offset_entry);
				size_t const index = byte_offset_entry / entry_size;

				RE_DBG_ASSERT(entry->usecount == 0);
				
				// destroy object
				destructor(&entry->object);

				if(last_allocated_object_after == byte_offset_entry + entry_size)
				{
					last_allocated_object_after = 0;
					for(size_t i = byte_offset_entry; i != 0; i -= entry_size)
					{
						Entry const * data_i = reinterpret_cast<Entry*>(reinterpret_cast<byte*>(data.data())+i);
						if(data_i->usecount != 0)
						{
							last_allocated_object_after = i+byte_offset_entry;
							break;
						}
					}
				}

				if(firstFree > index)
				{
					entry->nextFree = firstFree;
					firstFree = index;
				}
				else
				{
					for(size_t i = byte_offset_entry; i!=0; i-=entry_size)
					{
						Entry const * data_i = reinterpret_cast<Entry*>(reinterpret_cast<byte*>(data.data())+i);
						if(data_i->usecount == 0)
						{
							entry->nextFree = data_i->nextFree;
							data_i->nextFree = index;
							break;
						}
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
			/*Allocates a new instance in the pool and initializes it with the given arguments.
			@param[in] args: the arguments to be passed to the constructor of the allocated instance.
			@return: a unique_handle pointing to the allocated instance.*/
			unique_handle<T> alloc(Args&&... args)
			{
				if(firstFree == -1)
				{
					data.emplace_back();
					Entry & back = data.back();
					back.usecount = 1;
					size_t const byte_offset_entry = (data.size()-1) * entry_size;
					size_t const byte_offset_object = byte_offset_entry + offsetof(Entry, object);
					unique_handle<T> ret(*this,byte_offset_entry, byte_offset_object);
					back.usecount--;
					new (&back.object) T(std::forward<Args>(args)...);
					return ret;
				}
				else
				{
					size_t const index = firstFree;
					firstFree = data[firstFree].nextFree;

					data[index].usecount = 1;
					size_t const byte_offset_entry = index * entry_size;
					size_t const byte_offset_object = byte_offset_entry + offsetof(Entry, object);
					unique_handle<T> ret(*this, byte_offset_entry, byte_offset_object);
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
			size_t byte_offset_entry;
			size_t byte_offset_object;

			_RE_HANDLE_INSPECT_MEMBER_DECL

			strong_handle(MemoryPool<T> &pool, size_t byte_offset_entry, size_t byte_offset_object) : pool(&pool), byte_offset(byte_offset) { pool.inc_ref(byte_offset); }
			
		public:
			strong_handle() : pool(nullptr), byte_offset(-1) { _RE_HANDLE_INSPECT_UPDATE }
			strong_handle(nullptr_t) : pool(nullptr), byte_offset(-1) { _RE_HANDLE_INSPECT_UPDATE }

			strong_handle(const strong_handle<T> &copy) : pool(copy.pool), byte_offset(copy.byte_offset) { if(pool)pool->inc_ref(byte_offset); _RE_HANDLE_INSPECT_UPDATE }
			strong_handle(strong_handle<T> &&move) { operator=(std::move(move)); }
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

#include "MemoryPool.inl"

#endif