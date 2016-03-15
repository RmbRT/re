#include "FrameBuffer.hpp"
#include "OpenGL.hpp"

namespace re
{
	namespace graphics
	{
		namespace GL
		{
			FrameBuffer::FrameBuffer():
				Handle(),
				m_color(),
				m_depth(),
				m_stencil(),
				m_depth_stencil()
			{
			}

			FrameBuffer::FrameBuffer(FrameBuffer && move):
				Handle(std::move(move)),
				m_color(std::move(move.m_color)),
				m_depth(std::move(move.m_depth)),
				m_stencil(std::move(move.m_stencil)),
				m_depth_stencil(std::move(move.m_depth_stencil))
			{
			}

			FrameBuffer & FrameBuffer::operator=(FrameBuffer && move)
			{
				if(this == &move)
					return *this;

				static_cast<Handle&>(*this) = std::move(move);
				m_color = std::move(move.m_color);
				m_depth = std::move(move.m_depth);
				m_stencil = std::move(move.m_stencil);
				m_depth_stencil = std::move(move.m_depth_stencil);

				return *this;
			}

			void FrameBuffer::bind_read()
			{
				RE_DBG_ASSERT(exists() && "Tried to bind nonexisting frame buffer!");

				if(bound_read != handle())
				{
					RE_OGL(glBindFramebuffer(GL_READ_FRAMEBUFFER, handle()));
					bound_read = handle();
				}
			}

			void FrameBuffer::bind_write()
			{
				RE_DBG_ASSERT(exists() && "Tried to bind nonexisting frame buffer!");

				if(bound_write != handle())
				{
					RE_OGL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, handle()));
					bound_write = handle();
				}
			}

			void FrameBuffer::bind_both()
			{
				RE_DBG_ASSERT(exists() && "Tried to bind nonexisting frame buffer!");

				if(bound_read != handle() || bound_write != handle())
				{
					RE_OGL(glBindFramebuffer(GL_FRAMEBUFFER, handle()));
					bound_read = bound_write = handle();
				}
			}

			void FrameBuffer::unbind_read()
			{
				if(bound_read)
				{
					RE_OGL(glBindFramebuffer(GL_READ_FRAMEBUFFER, 0));
					bound_read = 0;
				}
			}

			void FrameBuffer::unbind_write()
			{
				if(bound_write)
				{
					RE_OGL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
					bound_write = 0;
				}
			}

			void FrameBuffer::unbind_both()
			{
				if(bound_read || bound_write)
				{
					RE_OGL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
					bound_read = bound_write = 0;
				}
			}

			void FrameBuffer::alloc(FrameBuffer * objects, size_t count)
			{
				handle_t * const handles = allocation_buffer(count);

				RE_OGL(glGenFramebuffers(count, handles));

				for(size_t i = count; i--;)
				{
					RE_DBG_ASSERT(!objects[i].exists() &&
						"Tried to alloc existing frame buffer!");

					objects[i].set_handle(handles[i]);
				}
			}

			void FrameBuffer::destroy(FrameBuffer * objects, size_t count)
			{
				handle_t * const handles = allocation_buffer(count);

				for(size_t i = count; i--;)
				{
					RE_DBG_ASSERT(objects[i].exists() &&
						"Tried to destroy nonexisting frame buffer!");
					RE_DBG_ASSERT(!objects[i].has_color() &&
						"Tried to destroy frame buffer with color attachment!");
					RE_DBG_ASSERT(!objects[i].has_depth() &&
						"Tried to destroy frame buffer with depth attachment!");
					RE_DBG_ASSERT(!objects[i].has_stencil() &&
						"Tried to destroy frame buffer with stencil attachment!");
					RE_DBG_ASSERT(!objects[i].has_depth_stencil() &&
						"Tried to destroy frame buffer with depth stencil attachment!");

					handles[i] = objects[i].handle();
					if(bound_read == objects[i].handle())
						bound_read = 0;
					if(bound_write == objects[i].handle())
						bound_write = 0;
					objects[i].null_handle();
				}

				RE_OGL(glDeleteFramebuffers(count, handles));
			}

			void FrameBuffer::blit(
					FrameBuffer * source,
					FrameBuffer * dest,
					math::uivec2 const& src_origin,
					math::uivec2 const& src_end,
					math::uivec2 const& dst_origin,
					math::uivec2 const& dst_end,
					bool blit_color,
					bool blit_depth,
					bool blit_stencil,
					bool interpolate)
			{
				if(source)
					RE_DBG_ASSERT(source->exists() &&
						"Tried to blit from nonexisting frame buffer!");
				if(dest)
					RE_DBG_ASSERT(dest->exists() &&
						"Tried to blit into nonexisting frame buffer!");

				GLenum mask = 0;

				if(blit_color)
				{
					if(source)
						RE_DBG_ASSERT(source->has_color() &&
							"Tried to blit color but source had no color!");
					if(dest)
						RE_DBG_ASSERT(dest->has_color() &&
							"Tried to blit color but dest had no color!");
					mask |= GL_COLOR_BUFFER_BIT;
				}
				if(blit_depth)
				{
					if(source)
						RE_DBG_ASSERT(source->has_depth() &&
							"Tried to blit depth but source had no depth!");
					if(dest)
						RE_DBG_ASSERT(dest->has_depth() &&
							"Tried to blit depth but dest had no depth!");
					mask |= GL_DEPTH_BUFFER_BIT;
				}
				if(blit_stencil)
				{
					if(source)
						RE_DBG_ASSERT(source->has_stencil() &&
							"Tried to blit stencil but source had no stencil!");
					if(dest)
						RE_DBG_ASSERT(dest->has_stencil() &&
							"Tried to blit stencil but dest had no stencil!");
					mask |= GL_STENCIL_BUFFER_BIT;
				}

				if(!source && !dest)
					unbind_both();
				else
				{
					if(source)
						source->bind_read();
					else
						unbind_read();
					if(dest)
						dest->bind_write();
					else
						unbind_write();
				}

				GLenum filter = interpolate ? GL_LINEAR : GL_NEAREST;

				RE_OGL(glBlitFramebuffer(
					src_origin.x,
					src_origin.y,
					src_end.x,
					src_end.y,
					dst_origin.x,
					dst_origin.y,
					dst_end.x,
					dst_end.y,
					mask,
					filter));	
			}

			void FrameBuffer::attach_color(Texture && color)
			{
				RE_DBG_ASSERT(!has_color() &&
					"Frame buffer had a color attachment already!");

				m_color = std::move(color);
				bind_write();
				RE_OGL(glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, color.handle(), 0));
			}

			void FrameBuffer::detach_color(Texture & out)
			{
				RE_DBG_ASSERT(has_color() &&
					"Frame buffer has no color attachment!");
				bind_write();
				RE_OGL(glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 0, 0));
				
				out = std::move(m_color);
			}

			void FrameBuffer::attach_depth(RenderBuffer && depth)
			{
				RE_DBG_ASSERT(!has_depth() &&
					"Frame buffer had a depth attachment already!");

				m_depth = std::move(depth);
				bind_write();
				RE_OGL(glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depth.handle(), 0));
			}

			void FrameBuffer::detach_depth(RenderBuffer & out)
			{
				RE_DBG_ASSERT(has_depth() &&
					"Frame buffer has no depth attachment!");

				out = std::move(m_depth);
				bind_write();
				RE_OGL(glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 0, 0));
			}

			void FrameBuffer::attach_stencil(RenderBuffer && stencil)
			{
				RE_DBG_ASSERT(!has_stencil() &&
					"Frame buffer had a stencil attachment already!");

				m_stencil = std::move(stencil);
				bind_write();
				RE_OGL(glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, stencil.handle(), 0));
			}

			void FrameBuffer::detach_stencil(RenderBuffer & out)
			{
				RE_DBG_ASSERT(has_stencil() &&
					"Frame buffer has no stencil attachment!");

				out = std::move(m_stencil);
				bind_write();
				RE_OGL(glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, 0, 0));
			}

			void FrameBuffer::attach_depth_stencil(RenderBuffer && depth_stencil)
			{
				RE_DBG_ASSERT(!has_depth_stencil() &&
					"Frame buffer had a depth stencil attachment already!");

				m_depth_stencil = std::move(depth_stencil);
				bind_write();
				RE_OGL(glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, depth_stencil.handle(), 0));
			}

			void FrameBuffer::detach_depth_stencil(RenderBuffer & out)
			{
				RE_DBG_ASSERT(has_depth_stencil() &&
					"Frame buffer has no depth stencil attachment!");

				out = std::move(m_depth_stencil);
				bind_write();
				RE_OGL(glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, 0, 0));
			}

		}
	}
}