#ifndef __re_util_notnull_hpp_defined
#define __re_util_notnull_hpp_defined

#include "../defines.hpp"

namespace re
{
	namespace util
	{

		template<class T>
		/** Stores a pointer to an object, which is guaranteed not to be null.
		Note that this does not affect the lifetime of the referenced object in any way,
		as it is treated like a normal reference or pointer. Note that, to access the element pointed to by notnull,
		you have to use the pointer syntax (->). */
		struct notnull
		{
			T* m_data;
		public:
			notnull(T *data);

			RECX constexpr operator T*() const;
		};
	}
}

#include "NotNull.inl"

#endif
