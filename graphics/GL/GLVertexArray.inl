namespace re
{
	namespace graphics
	{
		namespace GL
		{
			GLVertexArrayBase::~GLVertexArrayBase()
			{
				RE_DBG_ASSERT(!exists() && "Vertex Array was not properly destroyed!");
			}

			template<class Vertex>
			GLVertexArray<Vertex>::GLVertexArray(
				BufferAccess access,
				BufferUsage usage):
				GLVertexArrayBase(access, usage)
			{
			}
			template<class Vertex>
			GLVertexArray<Vertex>::GLVertexArray(GLVertexArray<Vertex> &&move):
				GLVertexArrayBase(std::move(move))
			{
			}

			template<class Vertex>
			void GLVertexArray<Vertex>::alloc(GLVertexArray<Vertex> * arrays, size_t count)
			{
				static_assert(sizeof(GLVertexArray<Vertex>) == sizeof(GLVertexArrayBase),
					"Must not add members to GLVertexArray<T>.");

				GLVertexArrayBase::alloc(arrays, count);
			}

			template<class Vertex>
			void GLVertexArray<Vertex>::destroy(GLVertexArray<Vertex> * arrays, size_t count)
			{
				static_assert(sizeof(GLVertexArray<Vertex>) == sizeof(GLVertexArrayBase),
					"Must not add members to GLVertexArray<T>.");
				
				GLVertexArrayBase::destroy(arrays, count);
			}

			template<class Vertex>
			void GLVertexArray<Vertex>::configure(VertexType<Vertex> const& type_description)
			{
				static_cast<GLVertexArrayBase*>(this)
					->configure(
						type_description.elements,
						type_description.VERTEX_ELEMENTS,
						type_description.VERTEX_SIZE);
			}

			template<class Vertex>
			void GLVertexArray<Vertex>::set_data(Vertex const * data, size_t count)
			{
				static_cast<GLVertexArrayBase*>(this)
					->set_data(data, count, sizeof(Vertex));
			}
		}
	}
}