#ifndef __re_mathutil_hpp_defined
#define __re_mathutil_hpp_defined

#include "../base_types.hpp"
#include "../defines.hpp"

#include <array>

namespace re
{
	namespace math
	{
		template<class T>
		inline const T &min(const T &a, const T &b) { return (a<b)?(const T&)a:(const T&)b; }
		template<class T>
		inline const T &max(const T &a, const T &b) { return (a<b)?(const T&)b:(const T&)a; }

		template<class T>
		inline const T &cap(const T &val, const T &_min, const T &_max) { return min(max(val,_min),_max); }

		template<class T, size_t sz>
		T avg(std::array<T, sz> const&x)
		{
			T acc = T();
			for(size_t z = sz; z--;)
				acc = acc + x[z];
			if(sz)
				return acc / (int)sz;
			else
				return T();
		}
	}
}

#endif