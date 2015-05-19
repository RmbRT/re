#include "ShaderType.hpp"

#define _ENUM_CASE(X) case X: return #X; break;

namespace re
{
	namespace graphics
	{
		const char* RE_ENUMToString(ShaderType type)
		{
			switch(type)
			{
			_ENUM_CASE(ShaderType::ST_VERTEX)
			_ENUM_CASE(ShaderType::ST_FRAGMENT)
			_ENUM_CASE(ShaderType::ST_GEOMETRY)
			_ENUM_CASE(ShaderType::ST_TESS_CONTROL)
			_ENUM_CASE(ShaderType::ST_TESS_EVALUATION)
			default: return "";
			}
		}
	}
}