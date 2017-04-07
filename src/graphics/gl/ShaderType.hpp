#ifndef __re_graphics_gl_shadertype_hpp_defined
#define __re_graphics_gl_shadertype_hpp_defined

#include "../../defines.hpp"
#include "../../types.hpp"

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			/** Contains the available shader types. */
			enum class ShaderType
			{
				/** Vertex shader. */
				kVertex,
				/** Fragment (pixel) shader. */
				kFragment,
				/** Geometry shader. */
				kGeometry,
				/** Tesselation control shader. */
				kTesselationControl,
				/** Tesselation evaluation shader. */
				RE_LAST(kTesselationEvaluation)
			};


			string8_t const& enum_to_string(
				ShaderType type);
		}
	}
}


#endif