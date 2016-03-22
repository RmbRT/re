#include "Buffer.hpp"
#include "OpenGL.hpp"

namespace re
{
	namespace graphics
	{
		namespace GL
		{
			Buffer::Buffer(
				BufferType type,
				BufferAccess access,
				BufferUsage usage):
				Handle(),
				m_type(type),
				m_access(access),
				m_usage(usage)
			{
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

			void Buffer::bind()
			{
				if(exists() && bound != handle())
				{
					RE_OGL(glBindBuffer(opengl_target(m_type), handle()));
					bound = handle();
				}
			}

			void Buffer::alloc_handles(handle_t * handles, size_t count)
			{
				RE_OGL(glGenBuffers(count, handles));
			}

			void Buffer::alloc(Buffer * buffers, size_t count)
			{
				for(size_t i = count; i--;)
					RE_DBG_ASSERT(!buffers[i].exists() &&
						"Tried to allocate existing Buffer!");

				handle_t * const handles = allocation_buffer(count);

				alloc_handles(handles, count);

				for(size_t i = count; i--;)
					buffers[i].set_handle(handles[i]);
			}

			void Buffer::destroy_handles(handle_t * handles, size_t count)
			{
				RE_OGL(glDeleteBuffers(count, handles));
			}

			void Buffer::destroy(Buffer * buffers, size_t count)
			{
				handle_t * const handles = allocation_buffer(count);

				for(size_t i = count; i--;)
				{
					RE_DBG_ASSERT(buffers[i].exists() &&
						"Tried to destroy nonexisting Buffer!");

					handles[i] = buffers[i].handle();

					if(bound == buffers[i].handle())
						bound = 0;

					buffers[i].null_handle();
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

			void Buffer::data(void const * data, size_t elements, size_t element_size)
			{
				bind();

				GLenum target = opengl_target(m_type);
				GLenum usage = opengl_usage(m_access, m_usage);
				
				RE_OGL(glBufferData(target, elements*element_size, data, usage));
			}
		}
	}
}