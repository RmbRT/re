#ifndef __re_graphics_gl_glbuffer_hpp_defined
#define __re_graphics_gl_glbuffer_hpp_defined

#include "../../types.hpp"
#include "../../defines.hpp"
#include "GLHandle.hpp"

namespace re
{
	namespace graphics
	{
		namespace GL
		{
			enum class BufferType
			{
				VertexData,
				IndexData
			};

			enum class BufferAccess
			{
				Stream,
				Static,
				Dynamic
			};

			enum class BufferUsage
			{
				Draw,
				Read,
				Copy
			};

			/* Represents an OpenGL buffer object.
			Does not support copy operations.
			Must be released manually.
			Allocate / destroy multiple objects at once for more efficiency. */
			class GLBuffer : GLHandle
			{	friend class GLVertexArrayBase;
				static gl_handle_t bound;

				BufferType m_type;
				BufferAccess m_access;
				BufferUsage m_usage;
			public:
				GLBuffer(BufferType type, BufferAccess access, BufferUsage usage);
				GLBuffer(GLBuffer &&);
				GLBuffer &operator=(GLBuffer &&);
				REINL ~GLBuffer(); /* Checks whether the GLBuffer was released. */

				GLBuffer(GLBuffer const&) = delete;
				GLBuffer &operator=(GLBuffer const&) = delete;

				void bind();
				static void alloc(GLBuffer * buffers, size_t count);
				static void destroy(GLBuffer * buffers, size_t count);

				using GLHandle::exists;
				using GLHandle::gl_handle;

				/* Sets the data stored on the GPU.
				@param[in] data: the data that is to be stored on the GPU.
				@param[in] elements: the count of elements in data.
				@param[in] element_size: the type size of the elements in data. */
				void data(void const* data, size_t elements, size_t element_size);

			private:
				static void alloc_handles(gl_handle_t * handles, size_t count);
				static void destroy_handles(gl_handle_t * handles, size_t count);
			};
		}
	}
}

#include "GLBuffer.inl"

#endif