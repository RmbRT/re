#ifndef __re_shadertype_hpp_defined
#define __re_shadertype_hpp_defined

#include "../defines.hpp"

namespace re
{
	namespace graphics
	{
		/** Contains the available shader types. */
		enum class ShaderType
		{
			/** Vertex shader. */
			ST_VERTEX,
			/** Fragment (pixel) shader. */
			ST_FRAGMENT,
			/** Geometry shader. */
			ST_GEOMETRY,
			/** Tesselation control shader. */
			ST_TESS_CONTROL,
			/** Tesselation evaluation shader. */
			ST_TESS_EVALUATION
		};

		const int ST_COUNT = 5;

		inline const char* enumToString(ShaderType type);
	}
}

#endif