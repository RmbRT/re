/** @file NotNull.hpp
	Contains the safe NotNull pointer utility class. */
#ifndef __re_util_notnull_hpp_defined
#define __re_util_notnull_hpp_defined

#include "../defines.hpp"

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
			/** Constructs a non-null pointer.
			@assert
				The given pointer must not be null. */
			RECXDA NotNull(T *data);

			/** Returns the pointer held by the structure. */
			RECX operator T*() const;
		};

		template<class T>
		/** Array types of unspecified size are treated as pointers. */
		struct NotNull<T[]> : private NotNull<T>
		{
			using NotNull<T>::NotNull;
		};

		template<class T>
		/** Shorthand notation that allows omitting the template argument. */
		RECX NotNull<T> notNull(T *);
	}
}

#include "NotNull.inl"

#endif
