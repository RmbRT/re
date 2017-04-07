/** @file NotNull.hpp
	Contains the safe NotNull pointer utility class. */
#ifndef __re_util_notnull_hpp_defined
#define __re_util_notnull_hpp_defined

#include "../defines.hpp"
#include <type_traits>

namespace re
{
	namespace util
	{

		template<class T>
		/** Stores a pointer to an object, which is guaranteed not to be null.
		Note that this does not affect the lifetime of the referenced object in any way, as it is treated like a normal reference or pointer. Modifying the stored pointer is only possible by reassigning, because the new value has to be checked for validity. In release / non-assertion mode, all checks are disabled, so that after extensive debug testing, the overhead of checking pointer values will be removed. */
		struct NotNull
		{
			T* m_data;
		public:

			NotNull(nullptr_t) = delete;

			/** Constructs a non-null pointer.
			@assert
				The given pointer must not be null. */
			RECXDA NotNull(T * data);

			template<class X>
			RECXDA explicit NotNull(X * data);

			/** Returns the pointer held by the structure. */
			RECXDA operator T*() const;

			RECXDA T * operator->() const;
			RECXDA T & operator*() const;

			template<class X>
			RECXDA operator typename std::enable_if<
				std::is_convertible<T *, X *>::value,
				X *>::type () const;
		};

		template<class T>
		/** Array types of unspecified size are treated as pointers. */
		struct NotNull<T[]> : private NotNull<T>
		{
			using NotNull<T>::NotNull;
			using NotNull<T>::operator T*;
			using NotNull<T>::operator->;
			using NotNull<T>::operator*;
		};

		template<class T>
		/** Shorthand notation that allows omitting the template argument. */
		RECX NotNull<T> notNull(T *);

		template<class To, class From>
		RECXDA NotNull<To> reinterpret(NotNull<From>);
	}
}

#include "NotNull.inl"

#endif
