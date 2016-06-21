#ifndef __re_graphics_gl_renderbuffer_hpp_defined
#define __re_graphics_gl_renderbuffer_hpp_defined

#include "../../defines.hpp"
#include "Handle.hpp"

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			class RenderBuffer : Handle
			{
				static handle_t bound;

				uint32_t
					m_width,
					m_height;
			public:
				/**  . */
				RenderBuffer();
				RenderBuffer(RenderBuffer &&) = default;
				RenderBuffer &operator=(RenderBuffer &&) = default;

				RenderBuffer(RenderBuffer const&) = delete;
				RenderBuffer &operator=(RenderBuffer const&) = delete;

				static void alloc(RenderBuffer * objects, size_t count);
				static void destroy(RenderBuffer * objects, size_t count);

				void resize(uint32_t width, uint32_t height);
				REIL uint32_t width() const;
				REIL uint32_t height() const;

				using Handle::handle;
				using Handle::exists;

				void bind();
				static void unbind();
			};
		}
	}
}

#include "RenderBuffer.inl"

#endif