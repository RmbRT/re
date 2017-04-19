#ifndef __re_util_pointer_hpp_defined
#define __re_util_pointer_hpp_defined

#include "../defines.hpp"
#include "../base_types.hpp"
#include "RefCount.hpp"
#include "Heap.hpp"

namespace re
{
	namespace util
	{
		template<class T>
		/** Pointer class that deallocates the held pointer after the last object referencing to it is destroyed.
			This allows copying and moving. */
		class Shared
		{
			RefCount<T> * m_obj;

			void unref();
			Shared(RefCount<T> & obj);
		public:
			RECX Shared();
			RECX Shared(nullptr_t);
			Shared(Shared<T> const&);
			Shared(Shared<T> &&);
			Shared &operator=(Shared<T> const&);
			Shared &operator=(Shared<T> &&);
			~Shared();

			REIL T* operator->() const;
			REIL T& operator*() const;
			RECX operator bool() const;

			template<class ...Args>
			static Shared<T> alloc(Args && ...);
		};

		template<class T>
		/** Pointer class that deallocates the held pointer upon destruction.
			This makes it impossible to copy it, only moving is allowed. */
		class Auto
		{
		protected:
			T * m_obj;
		public:
			Auto();
			Auto(Auto<T> &&);
			Auto<T> &operator=(Auto<T> &&);
			Auto(T *);
			Auto<T> &operator=(T *);
			~Auto();

			REIL operator bool() const;

			/** Releases the pointer without freeing it.
				This resets the pointer to null.
			@return
				The address previously held by the pointer. */
			T * release();

			REIL T* operator->() const;
		};

		template<class T>
		class Auto<T []> : private Auto<T>
		{
			using Auto<T>::m_obj;
		public:
			Auto() = default;
			Auto(Auto &&) = default;
			using Auto<T>::operator->;
			using Auto<T>::release;

			Auto<T []> &operator=(Auto<T []> &&);
			Auto<T []> &operator=(T * ptr);
			Auto(T * ptr);
			~Auto();

			REIL T const& operator[](size_t i) const;
			REIL T &operator[](size_t i);
		};
	}
}

#include "Pointer.inl"

#endif