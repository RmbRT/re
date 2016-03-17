#ifndef __re_ray_hpp_defined
#define __re_ray_hpp_defined

#include "Vector.hpp"

namespace re
{
	namespace math
	{
		template<class T>
		struct Ray
		{
			Ray(vec3<T> &position, vec3<T> &direction) : position(position), direction(direction) { }

			vec3<T> position;
			vec3<T> direction;
		};
	}
}

#endif