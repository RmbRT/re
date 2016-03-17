#ifndef __re_vertex_hpp_defined
#define __re_vertex_hpp_defined

#include "..\math\Vector.hpp"

namespace re
{
	namespace graphics
	{
		struct Vertex;

		typedef Vertex Triangle[3];

		void calcNormal(Triangle tri);

		struct Vertex
		{
			Vertex();
			Vertex(const math::float3 &position, const math::float2 &texture, const math::float4 &color);
			Vertex(const math::float3 &position, const math::float2 &texture, const math::float4 &color, const math::float3 &normal);

			math::float3 position;
			math::float2 texture;
			math::float4 color;
			math::float3 normal;
		};

	}
}

#endif