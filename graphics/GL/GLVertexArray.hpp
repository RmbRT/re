#ifndef __re_graphics_gl_glvertexarray_hpp_defined
#define __re_graphics_gl_glvertexarray_hpp_defined

#include "../../types.hpp"
#include "../../defines.hpp"
#include "GLHandle.hpp"
#include "GLBuffer.hpp"

namespace re
{
	namespace graphics
	{
		namespace GL
		{
			enum class ElementType
			{
				Float,
				Double
			};

			struct VertexElement
			{
				ElementType type;
				size_t elements;
				size_t offset;
			};
			

#define RE_VERTEX_ELEMENT(VertexClass,ElementName) \
	(VertexElement	\
	{	\
		static_cast<decltype(VertexClass::ElementName) *>(0)->ELEM_TYPE,	\
		static_cast<decltype(VertexClass::ElementName) *>(0)->ELEM_COUNT,	\
		offsetof(VertexClass,ElementName)	\
	})


			template<class Vertex>
			struct VertexType
			{
				enum
				{
					VERTEX_SIZE = sizeof(Vertex),
					VERTEX_ELEMENTS = Vertex::ELEMENTS
				};
				VertexElement elements[VERTEX_ELEMENTS];
			};

			
			/* Contains rendering modes for drawing models.
			!!!IMPORTANT: ENUM VALUES MuST NOT CHANGE (lookup table in .cpp)!!! */
			enum class RenderMode
			{
				RM_LINE_STRIP,
				RM_LINES,
				RM_TRIANGLES,
				RM_TRIANGLE_STRIP,
				RM_POINTS,
				RM_QUADS,
				RM_QUAD_STRIP,
				RM_TRIANGLE_FAN
			};

			class GLVertexArrayBase : GLHandle
			{
				static gl_handle_t bound;
				GLBuffer
					m_vertex,
					m_index;
				bool m_index_used;
				RenderMode m_render_mode;
			public:
				/* Creates an invalid handle. */
				GLVertexArrayBase(BufferAccess access, BufferUsage usage);
				/* Moves the ownership of the array from one instance to another. */
				GLVertexArrayBase(GLVertexArrayBase &&);
				/* Moves the ownership of the array from one instance to another.
				The destination instance must not have an existing handle already. */
				GLVertexArrayBase &operator=(GLVertexArrayBase &&);
				/* Asserts that the vertex array must not exist anymore. */
				REINL ~GLVertexArrayBase();
			
				GLVertexArrayBase(GLVertexArrayBase const&) = delete;
				GLVertexArrayBase &operator=(GLVertexArrayBase const&) = delete;

				/* Binds the vertex array to select it for future OpenGL calls. */
				void bind();

				using GLHandle::exists;
				using GLHandle::gl_handle;

				static void alloc_handles(gl_handle_t * handles, size_t count);
				static void alloc(GLVertexArrayBase * arrays, size_t count);
				static void destroy_handles(gl_handle_t * handles, size_t count);
				static void destroy(GLVertexArrayBase * arrays, size_t count);

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

				static void wireframe_rendering(bool wireframe);

				void draw(size_t count, size_t start);
			};

			
			template<class Vertex>
			class GLVertexArray : GLVertexArrayBase
			{
			public:
				GLVertexArray(BufferAccess access);
				GLVertexArray(GLVertexArray<Vertex> &&);
				GLVertexArray<buffers> &operator=(GLVertexArray<Vertex> &&);
				~GLVertexArray();

				GLVertexArray(GLVertexArray<Vertex> const&) = delete;
				GLVertexArray<buffers> &operator=(GLVertexArray<Vertex> const&) = delete;

				static void alloc(GLVertexArray<Vertex> * arrays, size_t count);
				static void destroy(GLVertexArray<Vertex> * arrays, size_t count);

				void configure(VertexType<Vertex> const& type_description);

				void set_data(Vertex const * data, size_t count);
			};
		}
	}
}

#include "GLVertexArray.inl"

#endif