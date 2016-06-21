namespace re
{
	namespace graphics
	{
		namespace gl
		{

			RECX VertexElement::VertexElement(
				ElementType type,
				size_t elements,
				size_t offset):
				type(type),
				elements(elements),
				offset(offset)
			{
			}
			
			VertexArrayBase::~VertexArrayBase()
			{
				RE_DBG_ASSERT(!exists() && "Vertex Array was not properly destroyed!");
			}

			template<class Vertex>
			RECX VertexArray<Vertex>::VertexArray(
				BufferAccess access,
				BufferUsage usage):
				VertexArrayBase(access, usage)
			{
			}

			template<class Vertex>
			void VertexArray<Vertex>::alloc(VertexArray<Vertex> * arrays, size_t count)
			{
				static_assert(sizeof(VertexArray<Vertex>) == sizeof(VertexArrayBase),
					"Must not add members to VertexArray<T>.");

				VertexArrayBase::alloc(arrays, count);
			}

			template<class Vertex>
			void VertexArray<Vertex>::destroy(VertexArray<Vertex> * arrays, size_t count)
			{
				static_assert(sizeof(VertexArray<Vertex>) == sizeof(VertexArrayBase),
					"Must not add members to VertexArray<T>.");
				
				VertexArrayBase::destroy(arrays, count);
			}

			template<class Vertex>
			void VertexArray<Vertex>::configure(VertexType<Vertex> const& type_description)
			{
				static_cast<VertexArrayBase*>(this)
					->configure(
						type_description.elements,
						type_description.VERTEX_ELEMENTS,
						type_description.VERTEX_SIZE);
			}

			template<class Vertex>
			void VertexArray<Vertex>::set_data(
				Vertex const * vertex_data,
				size_t vertices,
				RenderMode render_mode)
			{
				static_cast<VertexArrayBase*>(this)
					->set_data(
						vertex_data,
						vertices,
						sizeof(Vertex),
						render_mode);
			}

			template<class Vertex>
			void VertexArray<Vertex>::set_data(
				Vertex const * vertex_data,
				size_t vertices,
				RenderMode render_mode,
				uint32_t const * index_data,
				size_t indices)
			{
				if(!indices)
					set_data(vertex_data, vertices, render_mode);
				else
					static_cast<VertexArrayBase*>(this)
						->set_data(
							vertex_data,
							vertices,
							sizeof(Vertex),
							render_mode,
							index_data,
							indices);
			}
		}
	}
}