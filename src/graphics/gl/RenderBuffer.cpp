#include "RenderBuffer.hpp"
#include "OpenGL.hpp"

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			RenderBuffer::RenderBuffer():
				Handle(),
				m_width(0),
				m_height(0)
			{
			}

			RenderBuffer &RenderBuffer::operator=(RenderBuffer && move)
			{
				if(this == &move)
					return *this;

				static_cast<Handle&>(*this) = std::move(move);
				m_width = move.m_width;
				m_height = move.m_height;

				return *this;
			}

			void RenderBuffer::alloc(RenderBuffer * objects, size_t count)
			{
				handle_t * const handles = allocation_buffer(count);
				RE_OGL(glGenRenderbuffers(count, handles));

				for(size_t i = count; i--;)
				{
					RE_DBG_ASSERT(!objects[i].exists() &&
						"Tried to allocate existing render buffer!");

					objects[i].set_handle(handles[i]);
				}
			}

			void RenderBuffer::destroy(RenderBuffer * objects, size_t count)
			{
				handle_t * const handles = allocation_buffer(count);

				for(size_t i = count; i--;)
					handles[i] = objects[i].handle();

				RE_OGL(glDeleteRenderbuffers(count, handles));

				for(size_t i = count; i--;)
				{
					RE_DBG_ASSERT(objects[i].exists() &&
						"Tried to destroy nonexisting render buffer!");

					objects[i].null_handle();
				}
			}

			void RenderBuffer::resize(uint32 width, uint32 height)
			{
				RE_DBG_ASSERT(exists() && "Tried to resize nonexisting render buffer!");

				if(m_width == width && m_height == height)
					return;

				m_width = width;
				m_height = height;
				
				static GLenum const format = GL_DEPTH_COMPONENT;

				bind();
				RE_OGL(glRenderbufferStorage(GL_RENDERBUFFER, format, m_width, m_height));
			}

			void RenderBuffer::bind()
			{
				RE_DBG_ASSERT(exists() && "Tried to bind nonexisting render buffer!");

				if(bound != handle())
				{
					RE_OGL(glBindRenderbuffer(GL_RENDERBUFFER, handle()));
					bound = handle();
				}
			}

			void RenderBuffer::unbind()
			{
				if(bound)
				{
					RE_OGL(glBindRenderbuffer(GL_RENDERBUFFER, 0));
					bound = 0;
				}
			}


		}
	}
}