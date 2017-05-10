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
			math::fvec3_t position;
			/** The direction of spot lights and directional global lights. */
			math::fvec3_t direction;
			/** The angle for spot lights. If zero, the light is considered as shining into all directions. */
			float angle;
			/** The light color. */
			math::fvec3_t color;
		};
	}
}


#endif