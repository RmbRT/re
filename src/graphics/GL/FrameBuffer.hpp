#ifndef __re_graphics_gl_framebuffer_hpp_defined
#define __re_graphics_gl_framebuffer_hpp_defined

#include "../../defines.hpp"
#include "../../types.hpp"
#include "Handle.hpp"
#include "RenderBuffer.hpp"
#include "Texture.hpp"

#include "../../math/Vector.hpp"

namespace re
{
	namespace graphics
	{
		namespace GL
		{
			class FrameBuffer : Handle
			{
				static handle_t bound_read;
				static handle_t bound_write;
				
				uint32
					m_width,
					m_height;

				Texture m_color;
				RenderBuffer m_depth;
				RenderBuffer m_stencil;
				RenderBuffer m_depth_stencil;
				
			public:
				FrameBuffer();
				FrameBuffer(FrameBuffer &&) = default;
				FrameBuffer & operator=(FrameBuffer &&) = default;
				REINL ~FrameBuffer();

				FrameBuffer(FrameBuffer const&) = delete;
				FrameBuffer & operator=(FrameBuffer const&) = delete;


				void bind_read();
				void bind_write();
				void bind_both();

				static void unbind_read();
				static void unbind_write();
				static void unbind_both();

				static void alloc(FrameBuffer * objects, size_t count);
				static void destroy(FrameBuffer * objects, size_t count);

				/* buffer = null to use default (= window) buffer. */
				static void blit(
					FrameBuffer * source,
					FrameBuffer * dest,
					math::uivec2 const& src_origin,
					math::uivec2 const& src_end,
					math::uivec2 const& dst_origin,
					math::uivec2 const& dst_end,
					bool blit_color,
					bool blit_depth,
					bool blit_stencil,
					bool interpolate);

				void attach_color(Texture && color);
				void detach_color(Texture & out);
				REINL bool has_color() const;

				void attach_depth(RenderBuffer && depth);
				void detach_depth(RenderBuffer & out);
				REINL bool has_depth() const;

				void attach_stencil(RenderBuffer && stencil);
				void detach_stencil(RenderBuffer & out);
				REINL bool has_stencil() const;

				void attach_depth_stencil(RenderBuffer && depth_stencil);
				void detach_depth_stencil(RenderBuffer & out);
				REINL bool has_depth_stencil() const;
			};
		}
	}
}

#include "FrameBuffer.inl"

#endif