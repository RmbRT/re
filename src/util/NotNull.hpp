#ifndef __re_util_notnull_hpp_defined
#define __re_util_notnull_hpp_defined

#include "../defines.hpp"
#include "LogFile.hpp"

namespace re
{
	namespace util
	{

		template<class T>
		/*Stores a pointer to an object, which is guaranteed not to be null.
		Note that this does not affect the lifetime of the referenced object in any way,
		as it is treated like a normal reference or pointer. Note that, to access the element pointed to by notnull,
		you have to use the pointer syntax (->).*/
		struct notnull
		{
			T* m_data;
		public:
			notnull(T *data):
				m_data(data)
			{
				RE_DBG_ASSERT(m_data && "Tried to initialize with null!");
			}

			REINL constexpr operator T*() const
			{
				return m_data;
			}
		};
	}
}

#include "NotNull.inl"

#endif
