#ifndef __re_material_hpp_defined
#define __re_material_hpp_defined

#include "../math/Vector.hpp"

namespace re
{
	namespace graphics
	{
		struct Material
		{
			math::fvec3 ambient;
			math::fvec3 diffuse;
			math::fvec3 specular;
			float shininess;
		};
	}
}


#endif