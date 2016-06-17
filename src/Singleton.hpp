#ifndef __re_singleton_hpp_defined
#define __re_singleton_hpp_defined

#include "defines.hpp"

namespace re
{
	template<class T>
	T & singleton()
	{
		static T instance;
		return instance;
	}
}

#endif
