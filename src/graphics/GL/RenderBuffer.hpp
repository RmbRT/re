#ifndef __re_graphics_gl_renderbuffer_hpp_defined
#define __re_graphics_gl_renderbuffer_hpp_defined

#include "../../defines.hpp"
#include "Handle.hpp"

namespace re
{
	namespace graphics
	{
		namespace GL
		{
			class RenderBuffer : Handle
			{
				static handle_t bound;

				uint32
					m_width,
					m_height;
			public:
				/** */
				RenderBuffer();
				RenderBuffer(RenderBuffer &&) = default;
				RenderBuffer &operator=(RenderBuffer &&) = default;
				/** Asserts that the render buffer must not exist anymore. */
				REINL ~RenderBuffer();

				RenderBuffer(RenderBuffer const&) = delete;
				RenderBuffer &operator=(RenderBuffer const&) = delete;

				static void alloc(RenderBuffer * objects, size_t count);
				static void destroy(RenderBuffer * objects, size_t count);

				void resize(uint32 width, uint32 height);
				REINL uint32 width() const;
				REINL uint32 height() const;

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