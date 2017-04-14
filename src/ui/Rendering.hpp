#ifndef __re_ui_rendering_hpp_defined
#define __re_ui_rendering_hpp_defined

#include "../defines.hpp"
#include "../types.hpp"
#include "../graphics/gl/VertexArray.hpp"

namespace re
{
	namespace ui
	{
		/** The vertex type used for rendering user interfaces. */
		struct Vertex
		{
			math::fvec3_t position;
			math::fvec2_t texture;
			math::fvec4_t color;

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

#endif