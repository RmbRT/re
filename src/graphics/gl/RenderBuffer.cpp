#include "RenderBuffer.hpp"
#include "OpenGL.hpp"

#include "../../util/AllocationBuffer.hpp"

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			void RenderBuffer::alloc(
				RenderBuffer * const * objects,
				size_t count)
			{
				RE_DBG_ASSERT(objects != nullptr);

				handle_t * const handles = util::allocation_buffer<handle_t>(count);
				RE_OGL(glGenRenderbuffers(count, handles));

				for(size_t i = count; i--;)
				{
					RE_DBG_ASSERT(objects[i] != nullptr);
					RE_DBG_ASSERT(!objects[i]->exists() &&
						"Tried to allocate existing render buffer!");

					objects[i]->set_handle(handles[i]);
				}
			}

			void RenderBuffer::destroy(
				RenderBuffer * const * objects,
				size_t count)
			{
				RE_DBG_ASSERT(objects != nullptr);

				handle_t * const handles = util::allocation_buffer<handle_t>(count);

				for(size_t i = count; i--;)
				{
					RE_DBG_ASSERT(objects[i] != nullptr);
					handles[i] = objects[i]->handle();
				}

				RE_OGL(glDeleteRenderbuffers(count, handles));

				for(size_t i = count; i--;)
				{
					RE_DBG_ASSERT(objects[i]->exists() &&
						"Tried to destroy nonexisting render buffer!");

					objects[i]->null_handle();
				}
			}

			void RenderBuffer::resize(uint32_t width, uint32_t height)
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

				if(!bound())
				{
					RE_OGL(glBindRenderbuffer(GL_RENDERBUFFER, handle()));
					s_bound.bind(handle());
				}
			}

			void RenderBuffer::unbind()
			{
				if(!s_bound.empty())
				{
					RE_OGL(glBindRenderbuffer(GL_RENDERBUFFER, 0));
					s_bound.unbind();
				}
			}
		}
	}
}