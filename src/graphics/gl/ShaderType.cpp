#include "ShaderType.hpp"
#include "../../util/Lookup.hpp"

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			string8_t const& enum_to_string(ShaderType type)
			{
				static util::Lookup<ShaderType, string8_t> const k_lookup = {
					{ ShaderType::kVertex, "Vertex" },
					{ ShaderType::kFragment, "Fragment" },
					{ ShaderType::kGeometry, "Geometry" },
					{ ShaderType::kTesselationControl, "Tesselation control" },
					{ ShaderType::kTesselationEvaluation, "Tesselation evaluation" }
				};

				return k_lookup[type];
			}
		}
	}
}