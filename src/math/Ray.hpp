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
			Ray(
				Vec3<T> const& position,
				Vec3<T> const& direction):
				position(position),
				direction(direction)
			{
			}

			Vec3<T> position;
			Vec3<T> direction;
		};
	}
}

#endif