#ifndef __re_graphics_gl_vertexarray_hpp_defined
#define __re_graphics_gl_vertexarray_hpp_defined

#include "../../types.hpp"
#include "../../defines.hpp"
#include "Handle.hpp"
#include "Buffer.hpp"

#include "../../math/AxisAlignedBoundingBox.hpp"

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
				Warning: The enum values are linked with a lookup table in the .cpp file. The names are corresponding to the OpenGL render modes. */
			enum class RenderMode
			{
				LineStrip,
				Lines,
				Triangles,
				TriangleStrip,
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

				/** How many indices the array currently has. */
				size_t m_index_count;
				/** How many vertices the array currently has. */
				size_t m_vertex_count;
			public:
				/** Creates an invalid handle. */
				VertexArrayBase(
					BufferAccess access,
					BufferUsage usage);
				/** Moves the ownership of the array from one instance to another. */
				VertexArrayBase(
					VertexArrayBase &&);
				/** Moves the ownership of the array from one instance to another.
					The destination instance must not have an existing handle already. */
				VertexArrayBase &operator=(
					VertexArrayBase &&);
				/** Asserts that the vertex array must not exist anymore. */
				REIL ~VertexArrayBase();

				VertexArrayBase(
					VertexArrayBase const&) = delete;
				VertexArrayBase &operator=(
					VertexArrayBase const&) = delete;

				/** @return The render mode. */
				REIL RenderMode render_mode() const;
				/** @return The index buffer count. */
				REIL size_t index_count() const;
				/** @return The vertex buffer count. */
				REIL size_t vertex_count() const;
				/** @return If the index buffer is used, the index count, otherwise, the vertex count. */
				REIL size_t element_count() const;
				/** @return Whether the index buffer is used. */
				REIL bool index_used() const;

				/** Binds the vertex array to select it for future OpenGL calls. */
				void bind();

				using Handle::exists;
				using Handle::handle;

				static void alloc_handles(
					handle_t * handles,
					size_t count);
				static void alloc(
					VertexArrayBase * arrays,
					size_t count);
				static void destroy_handles(
					handle_t * handles,
					size_t count);
				static void destroy(
					VertexArrayBase * arrays,
					size_t count);

				/** Configures the VertexArray for the input type.
				@param[in] vertexType:
					An array of VertexElement descriptors,
					describing the fields of the input type.
				@param[in] element_count:
					The size of the array.
				@param[in] type_size:
					The size of the input type. */
				void configure(
					VertexElement const * vertexType,
					size_t element_count,
					size_t type_size);

				/** Sets the vertices with the given render mode.
					This will disable rendering from the index buffer, instead rendering from the vertex buffer.
				@assert
					The vertex array must exist. `vertex_data` must not be null.
				@param[in] vertex_data:
					The vertices to store on the GPU. Must be of the preconfigured vertex type.
				@param[in] vertices:
					The vertex count.
				@param[in] type_size:
					The vertex type's byte size.
				@param[in] render_mode:
					What rendering mode to use. */
				void set_data(
					void const * vertex_data,
					size_t vertices,
					size_t type_size,
					RenderMode render_mode);

				/** Sets the vertices and indices with the given render mode.
					This will enable rendering from the index buffer instead of the vertex buffer.
				@assert
					The vertex array must exist. `vertex_data` must not be null. `index_data` must not be null.
				@param[in] vertex_data:
					The vertices to store on the GPU. Must be of the preconfigured vertex type.
				@param[in] vertices:
					The vertex count.
				@param[in] type_size:
					The vertex type's byte size.
				@param[in] render_mode:
					The rendering mode.
				@param[in] index_data:
					The indices to store on the GPU.
				@param[in] indices:
					The element count of the index data. */
				void set_data(
					void const * vertex_data,
					size_t vertices,
					size_t type_size,
					RenderMode render_mode,
					uint32_t const * index_data,
					size_t indices);

				/** Draws `count` elements, starting at `start`. */
				void draw(size_t count, size_t start);

				/** Draws the whole array.
					Equivalent to `draw(element_count(), 0)`. */
				REIL void draw();
			};


			template<class Vertex>
			class VertexArray : public VertexArrayBase
			{
				std::vector<Vertex> m_data;
				math::faabb_t m_aabb;
			public:
				RECX VertexArray(BufferAccess access, BufferUsage usage);
				VertexArray(VertexArray<Vertex> &&) = default;
				VertexArray<Vertex> &operator=(VertexArray<Vertex> &&) = default;

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

				void set_data(
					std::vector<Vertex> vertex_data,
					RenderMode render_mode);

				void set_data(
					std::vector<Vertex> vertex_data,
					RenderMode render_mode,
					std::vector<uint32_t> index_data);

				using VertexArrayBase::draw;

				math::faabb_t const& aabb() const;
			};
		}
	}
}

#include "VertexArray.inl"

#endif
