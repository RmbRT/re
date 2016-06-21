#ifndef __re_util_refcount_hpp_defined
#define __re_util_refcount_hpp_defined

#include "../defines.hpp"

namespace re
{
	namespace util
	{
		template<class T>
		class RefCount
		{
			size_t m_count;
			T m_instance;
		public:
			template<class ...Args>
			REIL RefCount(Args && ... args);

			RECX14 T & get();
			RECX T const& get() const;

			RECX size_t count() const;

			REIL void reference();
			REIL size_t unreference();
		};
	}
}

#include "RefCount.inl"

#endif