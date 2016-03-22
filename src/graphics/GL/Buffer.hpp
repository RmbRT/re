#ifndef __re_graphics_gl_buffer_hpp_defined
#define __re_graphics_gl_buffer_hpp_defined

#include "../../types.hpp"
#include "../../defines.hpp"
#include "Handle.hpp"

namespace re
{
	namespace graphics
	{
		namespace GL
		{
			/** Whether a Buffer stores vertex data or index data. */
			enum class BufferType
			{
				VertexData,
				IndexData
			};

			/** The memory policy of a Buffer. */
			enum class BufferAccess
			{
				Stream,
				Static,
				Dynamic
			};

			/** The intention of a Buffer. */
			enum class BufferUsage
			{
				Draw,
				Read,
				Copy
			};

			/** Represents an OpenGL buffer object.
			Does not support copy operations.
			Must be released manually.
			Allocate / destroy multiple objects at once for more efficiency. */
			class Buffer : Handle
			{	friend class VertexArrayBase;
				static handle_t bound;

				BufferType m_type;
				BufferAccess m_access;
				BufferUsage m_usage;
			public:
				Buffer(BufferType type, BufferAccess access, BufferUsage usage);
				Buffer(Buffer &&) = default;
				Buffer &operator=(Buffer &&) = default;
				/** Asserts that the Buffer must not exist anymore. */
				REINL ~Buffer();

				/** Binds the Buffer. */
				void bind();
				/** Allocates the given Buffers.
				None of the given Buffers must be allocated yet. */
				static void alloc(Buffer * buffers, size_t count);
				/** Destroys the given Buffers.
				All of the given Buffers must be allocated.
				If the currently bound buffer is destroyed, it becomes unbound. */
				static void destroy(Buffer * buffers, size_t count);

				using Handle::exists;
				using Handle::handle;

				/** Sets the data stored on the GPU.
				@param[in] data: the data that is to be stored on the GPU.
				@param[in] elements: the count of elements in data.
				@param[in] element_size: the type size of the elements in data. */
				void data(void const* data, size_t elements, size_t element_size);

			private:
				/** Allocates the given Handles as Buffers. */
				static void alloc_handles(handle_t * handles, size_t count);
				/** Destroys the given Handles as Buffers.
				All of the given Handles must represent an existing Buffer. */
				static void destroy_handles(handle_t * handles, size_t count);
			};
		}
	}
}

#include "Buffer.inl"

#endif