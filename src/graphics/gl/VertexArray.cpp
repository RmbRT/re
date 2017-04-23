#include "VertexArray.hpp"
#include "OpenGL.hpp"

#include "../../util/Lookup.hpp"

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			VertexArrayBase::VertexArrayBase(
				BufferAccess access,
				BufferUsage usage):
				Handle(),
				m_vertex(BufferType::VertexData, access, usage),
				m_index(BufferType::IndexData, access, usage),
				m_index_used(false)
			{
			}
			VertexArrayBase::VertexArrayBase(
				VertexArrayBase && move):
				Handle(std::move(move)),
				m_vertex(std::move(move.m_vertex)),
				m_index(std::move(move.m_index)),
				m_index_used(move.m_index_used)
			{
			}

			VertexArrayBase &VertexArrayBase::operator=(
				VertexArrayBase && move)
			{
				if(this != &move)
				{
					static_cast<Handle&>(*this) = std::move(move);
					m_vertex = std::move(move.m_vertex);
					m_index = std::move(move.m_index);
					m_index_used = move.m_index_used;
				}
				return *this;
			}

			void VertexArrayBase::bind()
			{
				RE_DBG_ASSERT(exists() && "Tried to bind nonexisting vertex array!");

				if(bound != handle())
				{
					RE_OGL(glBindVertexArray(handle()));
					bound = handle();
				}
			}

			void VertexArrayBase::alloc_handles(
				handle_t * handles,
				size_t count)
			{
				RE_OGL(glGenVertexArrays(count, handles));
			}

			void VertexArrayBase::alloc(
				VertexArrayBase ** arrays,
				size_t count)
			{
				RE_DBG_ASSERT(arrays != nullptr);

				handle_t * buffer = allocation_buffer(count);

				VertexArrayBase::alloc_handles(buffer, count);

				for(size_t i = count; i--;)
				{
					RE_DBG_ASSERT(arrays[i] != nullptr);
					RE_DBG_ASSERT(!arrays[i].exists() &&
						"Tried to allocate existing vertex array!");

					arrays[i]->set_handle(buffer[i]);
				}
				buffer = allocation_buffer(count << 1);

				Buffer::alloc_handles(buffer, count);
				for(size_t i = count; i--;)
				{
					RE_DBG_ASSERT(!arrays[i]->m_vertex.exists() &&
						"Tried to allocate existing vertex buffer!");

					RE_DBG_ASSERT(!arrays[i]->m_index.exists() &&
						"Tried to allocate existing index buffer!");

					arrays[i]->m_vertex.set_handle(buffer[(i<<1)]);
					arrays[i]->m_index.set_handle(buffer[(i<<1)+1]);
				}
			}

			void VertexArrayBase::destroy_handles(
				handle_t * handles,
				size_t count)
			{
				for(size_t i = count; i--;)
					RE_DBG_ASSERT(handles[i] != 0
						&& "Tried to destroy nonexisting vertex array!");

				RE_OGL(glDeleteVertexArrays(count, handles));
			}

			void VertexArrayBase::destroy(
				VertexArrayBase ** arrays,
				size_t count)
			{
				handle_t * const buffers = allocation_buffer(count << 1);
				for(size_t i = count; i--;)
				{
					RE_DBG_ASSERT(arrays[i] != nullptr);
					RE_DBG_ASSERT(arrays[i]->m_vertex.exists() &&
						"Tried to destroy nonexisting vertex buffer!");
					RE_DBG_ASSERT(arrays[i]->m_index.exists() &&
						"Tried to destroy nonexisting index buffer!");

					buffers[(i<<1)] = arrays[i]->m_vertex.handle();
					buffers[(i<<1)+1] = arrays[i]->m_index.handle();
					arrays[i]->m_vertex.null_handle();
					arrays[i]->m_index.null_handle();
				}

				Buffer::destroy_handles(buffers, count << 1);

				handle_t * const vaos = allocation_buffer(count);

				for(size_t i = count; i--;)
				{
					RE_DBG_ASSERT(arrays[i].exists() &&
						"Tried to destroy nonexisting vertex array!");

					vaos[i] = arrays[i]->handle();
					arrays[i]->null_handle();
				}

				destroy_handles(vaos, count);
			}

			void VertexArrayBase::configure(
				VertexElement const * vertexType,
				size_t element_count,
				size_t type_size)
			{
				static util::Lookup<ElementType, GLenum> const k_type_lookup =
				{
					{ ElementType::Float, GL_FLOAT },
					{ ElementType::Double, GL_DOUBLE }
				};

				bind();

				for(size_t i = 0; i<element_count; i++)
				{
					RE_OGL(glEnableVertexAttribArray(i));
					RE_OGL(glVertexAttribPointer(
						i,
						vertexType[i].elements,
						k_type_lookup[vertexType[i].type],
						false,
						type_size,
						(void const*)vertexType[i].offset));
				}
			}

			void VertexArrayBase::set_data(
					void const * vertex_data,
					size_t vertices,
					size_t type_size,
					RenderMode render_mode)
			{
				RE_DBG_ASSERT(exists());
				m_vertex.data(vertex_data, vertices, type_size);
				m_index_used = false;
				m_render_mode = render_mode;
			}

			void VertexArrayBase::set_data(
					void const * vertex_data,
					size_t vertices,
					size_t type_size,
					RenderMode render_mode,
					uint32_t const * index_data,
					size_t indices)
			{
				RE_DBG_ASSERT(exists());
				m_vertex.data(vertex_data, vertices, type_size);
				m_index.data(index_data, indices, sizeof(index_data[0]));
				m_index_used = true;
				m_render_mode = render_mode;
			}

			void VertexArrayBase::draw(size_t count, size_t start)
			{
				static Lookup<RenderMode, GLenum> const k_rendermode_lookup =
				{
					{ RenderMode::Linestrip, GL_LINE_STRIP },
					{ RenderMode::Lines, GL_LINES },
					{ RenderMode::Triangles, GL_TRIANGLES },
					{ RenderMode::TriangleStrip, GL_TRIANGLE_STRIP },
					{ RenderMode::Points, GL_POINTS },
					{ RenderMode::TriangleFan, GL_TRIANGLE_FAN }
				};

				GLenum mode = k_rendermode_lookup[size_t(m_render_mode)];

				bind();

				if(m_index_used)
				{
					m_index.bind();
					RE_OGL(glDrawElements(mode, count, GL_UNSIGNED_INT, 0));
				} else
				{
					RE_OGL(glDrawArrays(mode, start, count));
				}
			}
		}
	}
}