#ifndef __re_ui_rendering_hpp_defined
#define __re_ui_rendering_hpp_defined

#include "../defines.hpp"
#include "../types.hpp"
#include "../graphics/gl/VertexArray.hpp"
#include "../math/Vector.hpp"

namespace re
{
	namespace ui
	{
		/** The vertex type used for rendering user interfaces. */
		struct Vertex
		{
			math::fvec2_t position;
			math::fvec2_t texture;
			math::fvec4_t color;

			Vertex() = default;
			RECX Vertex(
				math::fvec2_t const& position,
				math::fvec2_t const& texture,
				math::fvec4_t const& color);

			enum { ELEMENTS = 3 };

			static graphics::gl::VertexType<Vertex> const type;
		};

		typedef graphics::gl::VertexArray<Vertex> VertexArray;

		class Renderable
		{
			/** Whether the model needs to be refreshed. */
			mutable bool m_invalid;
			/** The model. */
			mutable VertexArray m_vertices;
		public:
			virtual void generate_model();
		};
	}
}

#include "Rendering.inl"

#endif