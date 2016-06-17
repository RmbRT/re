#ifndef __re_graphics_gl_vertexarray_hpp_defined
#define __re_graphics_gl_vertexarray_hpp_defined

#include "../../types.hpp"
#include "../../defines.hpp"
#include "Handle.hpp"
#include "Buffer.hpp"

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			enum class ElementType
			{
				Float,
				Double
			};

			struct VertexElement
			{
				VertexElement() = default;
				RECX VertexElement(
					ElementType type,
					size_t elements,
					size_t offset);

				ElementType type;
				size_t elements;
				size_t offset;
			};
			

#define RE_VERTEX_ELEMENT(VertexClass,ElementName) \
	re::graphics::gl::VertexElement( \
		static_cast<decltype(VertexClass::ElementName) *>(0)->ELEM_TYPE, \
		static_cast<decltype(VertexClass::ElementName) *>(0)->ELEM_COUNT, \
		offsetof(VertexClass,ElementName))


			template<class Vertex>
			/** Describes a vertex class. */
			struct VertexType
			{
				enum
				{
					/** The byte size of the Vertex. */
					VERTEX_SIZE = sizeof(Vertex),
					/** The count of the fields of the vertex. */
					VERTEX_ELEMENTS = Vertex::ELEMENTS
				};
				/** Describes the fields of the vertex. */
				VertexElement elements[VERTEX_ELEMENTS];
			};

			
			/** Contains rendering modes for drawing models.
				Warning: The enum values are linked with lookup table in .cpp file.
				The names are corresponding to the OpenGL render modes'. */
			enum class RenderMode
			{
				Linestrip,
				Lines,
				Triangles,
				Trianglestrip,
				Points,
				TriangleFan
			};

			/** The base class used for VertexArrays. */
			class VertexArrayBase : Handle
			{
				/** The currently bound VertexArray. */
				static handle_t bound;

				Buffer
					m_vertex,
					m_index;
				/** Whether the index buffer is in use. */
				bool m_index_used;
				/** How to render the stored vertices. */
				RenderMode m_render_mode;
			public:
				/** Creates an invalid handle. */
				VertexArrayBase(BufferAccess access, BufferUsage usage);
				/** Moves the ownership of the array from one instance to another. */
				VertexArrayBase(VertexArrayBase &&);
				/** Moves the ownership of the array from one instance to another.
				The destination instance must not have an existing handle already. */
				VertexArrayBase &operator=(VertexArrayBase &&);
				/** Asserts that the vertex array must not exist anymore. */
				REIL ~VertexArrayBase();
			
				VertexArrayBase(VertexArrayBase const&) = delete;
				VertexArrayBase &operator=(VertexArrayBase const&) = delete;

				/** Binds the vertex array to select it for future OpenGL calls. */
				void bind();

				using Handle::exists;
				using Handle::handle;

				static void alloc_handles(handle_t * handles, size_t count);
				static void alloc(VertexArrayBase * arrays, size_t count);
				static void destroy_handles(handle_t * handles, size_t count);
				static void destroy(VertexArrayBase * arrays, size_t count);

				/** Configures the VertexArray for the input type.
				@param[in] vertexType:
					An array of VertexElement descriptors,
					describing the fields of the input type.
				@param[in] element_count: The size of the array.
				@param[in] type_size: The size of the input type. */
				void configure(
					VertexElement const * vertexType,
					size_t element_count,
					size_t type_size);
				
				void set_data(
					void const * vertex_data,
					size_t vertices,
					size_t type_size,
					RenderMode render_mode);
				
				void set_data(
					void const * vertex_data,
					size_t vertices,
					size_t type_size,
					RenderMode render_mode,
					uint32_t const * index_data,
					size_t indices);

				void draw(size_t count, size_t start);
			};

			
			template<class Vertex>
			class VertexArray : VertexArrayBase
			{
			public:
				VertexArray(BufferAccess access, BufferUsage usage);
				VertexArray(VertexArray<Vertex> &&) = default;
				VertexArray<Vertex> &operator=(VertexArray<Vertex> &&) = default;
				~VertexArray();

				VertexArray(VertexArray<Vertex> const&) = delete;
				VertexArray<Vertex> &operator=(VertexArray<Vertex> const&) = delete;

				static void alloc(VertexArray<Vertex> * arrays, size_t count);
				static void destroy(VertexArray<Vertex> * arrays, size_t count);

				void configure(VertexType<Vertex> const& type_description);

				void set_data(
					Vertex const * vertex_data,
					size_t vertices,
					RenderMode render_mode);
				void set_data(
					Vertex const * vertex_data,
					size_t vertices,
					RenderMode render_mode,
					uint32_t const * index_data,
					size_t indices);

				using VertexArrayBase::draw;
			};
		}
	}
}

#include "VertexArray.inl"

#endif