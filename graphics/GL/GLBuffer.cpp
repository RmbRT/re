#include "GLBuffer.hpp"
#include "OpenGL.hpp"
#include <malloc.h>

namespace re
{
	namespace graphics
	{
		namespace GL
		{
			GLBuffer::GLBuffer(
				BufferType type,
				BufferAccess access,
				BufferUsage usage):
				GLHandle(),
				m_type(type),
				m_access(access),
				m_usage(usage)
			{
			}

			GLBuffer::GLBuffer(GLBuffer && move):
				GLHandle(std::move(move)),
				m_type(move.m_type),
				m_access(move.m_access),
				m_usage(move.m_usage)
			{
			}

			GLBuffer &GLBuffer::operator=(GLBuffer && move)
			{
				if(&move != this)
				{
					static_cast<GLHandle&>(*this) = std::move(move);
					m_type = move.m_type;
					m_access = move.m_access;
					m_usage = move.m_usage;
				}

				return *this;
			}

			REINL GLenum opengl_target(BufferType type)
			{
				static GLenum const table[] = {
					GL_ARRAY_BUFFER,
					GL_ELEMENT_ARRAY_BUFFER
				};
				RE_DBG_ASSERT(size_t(type) <= _countof(table));
				return table[size_t(type)];
			}

			void GLBuffer::bind()
			{
				if(exists() && bound != gl_handle())
				{
					RE_OGL(glBindBuffer(opengl_target(m_type), gl_handle()));
					bound = gl_handle();
				}
			}

			void GLBuffer::alloc_handles(gl_handle_t * handles, size_t count)
			{
				RE_OGL(glGenBuffers(count, handles));
			}

			void GLBuffer::alloc(GLBuffer * buffers, size_t count)
			{
				for(size_t i = count; i--;)
					RE_DBG_ASSERT(!buffers[i].exists() &&
						"Tried to allocate existing GLBuffer!");

				gl_handle_t * const handles = allocation_buffer(count);

				alloc_handles(handles, count);

				for(size_t i = count; i--;)
					buffers[i].set_gl_handle(handles[i]);
			}

			void GLBuffer::destroy_handles(gl_handle_t * handles, size_t count)
			{
				RE_OGL(glDeleteBuffers(count, handles));
			}

			void GLBuffer::destroy(GLBuffer * buffers, size_t count)
			{
				gl_handle_t * const handles = allocation_buffer(count);

				for(size_t i = count; i--;)
				{
					RE_DBG_ASSERT(buffers[i].exists() &&
						"Tried to destroy nonexisting GLBuffer!");

					handles[i] = buffers[i].gl_handle();

					if(bound == buffers[i].gl_handle())
						bound = 0;

					buffers[i].null_gl_handle();
				}

				destroy_handles(handles, count);
			}


			GLenum opengl_usage(BufferAccess access, BufferUsage usage)
			{
				static GLenum const table[][3] = {
					{
						GL_STREAM_DRAW,
						GL_STREAM_READ,
						GL_STREAM_COPY
					}, {
						GL_STATIC_DRAW,
						GL_STATIC_READ,
						GL_STATIC_COPY
					}, {
						GL_DYNAMIC_DRAW,
						GL_DYNAMIC_READ,
						GL_DYNAMIC_COPY
					}
				};

				RE_ASSERT(size_t(access) <= _countof(table));
				RE_ASSERT(size_t(usage) <= _countof(table[size_t(access)]));

				return table[size_t(access)][size_t(usage)];
			}

			void GLBuffer::data(void const * data, size_t elements, size_t element_size)
			{
				bind();

				GLenum target = opengl_target(m_type);
				GLenum usage = opengl_usage(m_access, m_usage);
				
				RE_OGL(glBufferData(target, elements*element_size, data, usage));
			}
		}
	}
}