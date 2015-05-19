#include "Vertex.hpp"

namespace re
{
	namespace graphics
	{
		Vertex::Vertex(): position(), color(), texture(), normal()	{	}
		Vertex::Vertex(const math::float3 &position, const math::float2 &texture, const math::float4 &color) : position(position), texture(texture), color(color), normal()	{	}
		Vertex::Vertex(const math::float3 &position, const math::float2 &texture, const math::float4 &color, const math::float3 &normal) : position(position), texture(texture), color(color), normal(normal)	{	}

		void calcNormal(Triangle tri)
		{
			math::float3 normal = math::cross(tri[1].position-tri[0].position, tri[2].position-tri[0].position);
			tri[0].normal = normal;
			tri[1].normal = normal;
			tri[2].normal = normal;
		}
	}
}