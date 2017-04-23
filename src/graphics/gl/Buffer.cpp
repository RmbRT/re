#include "Buffer.hpp"
#include "OpenGL.hpp"

#include "../../util/Lookup.hpp"

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			REIL GLenum opengl_target(
				BufferType type)
			{
				static util::Lookup<BufferType, GLenum> const table = {
					{BufferType::Array, GL_ARRAY_BUFFER},
					{BufferType::AtomicCounter, GL_ATOMIC_COUNTER_BUFFER},
					{BufferType::CopyRead, GL_COPY_READ_BUFFER},
					{BufferType::CopyWrite, GL_COPY_WRITE_BUFFER},
					{BufferType::DispatchIndirect, GL_DISPATCH_INDIRECT_BUFFER},
					{BufferType::DrawIndirect, GL_DRAW_INDIRECT_BUFFER},
					{BufferType::ElementArray, GL_ELEMENT_ARRAY_BUFFER},
					{BufferType::PixelPack, GL_PIXEL_PACK_BUFFER},
					{BufferType::PixelUnpack, GL_PIXEL_UNPACK_BUFFER},
					{BufferType::Query, GL_QUERY_BUFFER},
					{BufferType::ShaderStorage, GL_SHADER_STORAGE_BUFFER},
					{BufferType::Texture, GL_TEXTURE_BUFFER},
					{BufferType::TransformFeedback, GL_TRANSFORM_FEEDBACK_BUFFER},
					{BufferType::Uniform, GL_UNIFORM_BUFFER}
				};

				return table[type];
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

			void Buffer::alloc_handles(
				handle_t * handles,
				size_t count)
			{
				if(count)
				{
					RE_DBG_ASSERT(handles != nullptr);
					RE_OGL(glGenBuffers(count, handles));
				}
			}

			void Buffer::alloc(
				Buffer * const * buffers,
				size_t count)
			{
				if(!count)
					return;

				RE_DBG_ASSERT(buffers != nullptr);
				handle_t * const handles = allocation_buffer(count);

				alloc_handles(handles, count);

				for(size_t i = count; i--;)
				{
					RE_DBG_ASSERT(buffers[i] != nullptr);
					buffers[i]->set_handle(handles[i]);
				}
			}

			void Buffer::destroy_handles(
				handle_t * handles,
				size_t count)
			{
				if(count)
				{
					RE_DBG_ASSERT(handles != nullptr);
					RE_OGL(glDeleteBuffers(count, handles));
				}
			}

			void Buffer::destroy(
				Buffer * buffers,
				size_t count)
			{
				if(!count)
					return;

				RE_DBG_ASSERT(buffers != nullptr);

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