#include "Rendering.hpp"

using namespace re::graphics::gl;

namespace re
{
	namespace ui
	{
		VertexType<Vertex> const Vertex::type = {
			VertexElement(ElementType::Float, 3, offsetof(Vertex, position)),
			VertexElement(ElementType::Float, 2, offsetof(Vertex, texture)),
			VertexElement(ElementType::Float, 4, offsetof(Vertex, color))
		};
	}
}