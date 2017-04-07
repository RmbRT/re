#ifndef __re_material_hpp_defined
#define __re_material_hpp_defined

#include "../math/Vector.hpp"

namespace re
{
	namespace graphics
	{
		struct Material
		{
			math::fvec3_t ambient;
			math::fvec3_t diffuse;
			math::fvec3_t specular;
			float shininess;
		};
	}
}


#endif