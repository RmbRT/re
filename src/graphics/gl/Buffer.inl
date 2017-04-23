namespace re
{
	namespace graphics
	{
		namespace gl
		{
			RECX Buffer::Buffer(
				BufferType type,
				BufferAccess access,
				BufferUsage usage):
				Handle(),
				m_type(type),
				m_access(access),
				m_usage(usage)
			{
			}

			template<class Vertex>
			REIL VertexBuffer<Vertex>::VertexBuffer(
				BufferAccess access,
				BufferUsage usage):
				Buffer(
					BufferType::Array,
					access,
					usage)
			{
			}

			template<class Vertex>
			REIL void VertexBuffer<Vertex>::data(
				Vertex const * data,
				size_t elements) &
			{
				Buffer::data(
					data,
					elements,
					sizeof(Vertex));

				m_data.resize(elements);
				for(size_t i = 0; i < elements; i++)
					m_data[i] = data[i];
			}

			template<class Vertex>
			REIL void VertexBuffer<Vertex>::data(
				std::vector<Vertex> data) &
			{
				Buffer::data(
					data.data(),
					data.size(),
					sizeof(Vertex));

				m_data = std::move(data);
			}

			REIL IndexBuffer::IndexBuffer(
				BufferAccess access,
				BufferUsage usage):
				Buffer(
					BufferType::ElementArray,
					access,
					usage)
			{
			}

			REIL void IndexBuffer::data(
				index_t const * data,
				size_t elements) &
			{
				Buffer::data(
					data,
					elements,
					sizeof(index_t));

				m_data.resize(elements);
				for(size_t i = 0; i < elements; i++)
					m_data[i] = elements;
			}

			REIL void IndexBuffer::data(
				std::vector<index_t> data) &
			{
				Buffer::data(
					data.data(),
					data.size(),
					sizeof(index_t));

				m_data = std::move(data);
			}
		}
	}
}