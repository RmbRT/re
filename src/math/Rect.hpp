#ifndef __re_math_rect_hpp_defined
#define __re_math_rect_hpp_defined

#include "../defines.hpp"
#include "../base_types.hpp"

namespace re
{
	namespace math
	{
		template<class T>
		struct Rect
		{
			RECX Rect();
			RECX Rect(
				copy_arg_t<T> x,
				copy_arg_t<T> y,
				copy_arg_t<T> w,
				copy_arg_t<T> h);

			T x, y, w, h;
		};
	}
}

#include "Rect.inl"

#endif