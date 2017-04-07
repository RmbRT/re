#include "Buffer.hpp"
#include "OpenGL.hpp"

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			RECXDA GLenum opengl_target(
				BufferType type)
			{
				static GLenum const table[] = {
					GL_ARRAY_BUFFER,
					GL_ATOMIC_COUNTER_BUFFER,
					GL_COPY_READ_BUFFER,
					GL_COPY_WRITE_BUFFER,
					GL_DISPATCH_INDIRECT_BUFFER,
					GL_DRAW_INDIRECT_BUFFER,
					GL_ELEMENT_ARRAY_BUFFER,
					GL_PIXEL_PACK_BUFFER,
					GL_PIXEL_UNPACK_BUFFER,
					GL_QUERY_BUFFER,
					GL_SHADER_STORAGE_BUFFER,
					GL_TEXTURE_BUFFER,
					GL_TRANSFORM_FEEDBACK_BUFFER,
					GL_UNIFORM_BUFFER
				};

				RE_DBG_ASSERT(size_t(type) <= _countof(table));

				return table[size_t(type)];
			}

			void Buffer::bind() &
			{
				RE_DBG_ASSERT(exists() && "Tried to bind nonexisting Buffer.");

				if(!bindings[m_type].bound(handle()))
				{
					RE_OGL(glBindBuffer(opengl_target(m_type), handle()));
					bindings[m_type].bind(handle());
				}
			}

			void Buffer::alloc_handles(handle_t * handles, size_t count)
			{
				RE_OGL(glGenBuffers(count, handles));
			}

			void Buffer::alloc(Buffer * buffers, size_t count)
			{
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
					handles[i] = buffers[i].handle();

					if(bound == buffers[i].handle())
						bound = 0;

					buffers[i].null_handle();
				}

				destroy_handles(handles, count);
			}


			RECXDA GLenum opengl_usage(BufferAccess access, BufferUsage usage)
			{
				static util::Lookup<
					BufferAccess,
					util::Lookup<
						BufferUsage,
						GLenum> const table = {
					{
						BufferAccess::Stream,
						{
							{ BufferUsage::Draw, GL_STREAM_DRAW },
							{ BufferUsage::Read, GL_STREAM_READ },
							{ BufferUsage::Copy, GL_STREAM_COPY }
						}
					}, {
						BufferAccess::Static,
						{
							{ BufferUsage::Draw, GL_STATIC_DRAW },
							{ BufferUsage::Read, GL_STATIC_READ },
							{ BufferUsage::Copy, GL_STATIC_COPY }
						}
					}, {
						BufferAccess::Dynamic,
						{
							{ BufferUsage::Draw, GL_DYNAMIC_DRAW },
							{ BufferUsage::Read, GL_DYNAMIC_READ },
							{ BufferUsage::Copy, GL_DYNAMIC_COPY }
						}
					}
				};

				return table[access][usage];
			}

			void Buffer::data(void const * data, size_t elements, size_t element_size) &
			{
				bind();

				GLenum target = opengl_target(m_type);
				GLenum usage = opengl_usage(m_access, m_usage);

				RE_OGL(glBufferData(target, elements*element_size, data, usage));
			}
		}
	}
}