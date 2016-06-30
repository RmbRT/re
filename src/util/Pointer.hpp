#ifndef __re_util_pointer_hpp_defined
#define __re_util_pointer_hpp_defined

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

			REIL operator T*() const;

			template<class ...Args>
			Shared<T> alloc(Args && ...);
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

			/** releases the pointer without freeing it. */
			T * release();

			REIL operator T*() const;
		};

		template<class T>
		class Auto<T []> : private Auto<T>
		{
		public:
			Auto() = default;
			Auto(Auto &&) = default;
			using Auto<T>::operator T*;
			using Auto<T>::release;

			Auto<T []> &operator=(Auto<T []> &&);
			Auto<T []> &operator=(T * ptr);
			Auto(T * ptr);
			~Auto();
		};
	}
}

#include "Pointer.inl"

#endif