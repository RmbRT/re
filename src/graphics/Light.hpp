#ifndef __re_light_hpp_defined
#define __re_light_hpp_defined

#include "../math/Vector.hpp"

namespace re
{
	namespace graphics
	{
		struct Light
		{
			/** Used for describing the position of point lights.
			Ignored for directional global lights. */
			math::fvec3 position;
			/** The direction of spot lights and directional global lights. */
			math::fvec3 direction;
			/** The angle for spot lights. If zero, the light is considered as shining into all directions. */
			float angle;
			/** The light color. */
			math::fvec3 color;
		};
	}
}


#endif