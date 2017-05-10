#ifndef __re_graphics_gl_buffer_hpp_defined
#define __re_graphics_gl_buffer_hpp_defined

#include "../../types.hpp"
#include "../../defines.hpp"

#include "Handle.hpp"
#include "Binding.hpp"

#include "../../util/Lookup.hpp"

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			typedef unsigned int index_t;

			/** Whether a Buffer stores vertex data or index data. */
			enum class BufferType
			{
				/** Vertex data. */
				Array,
				AtomicCounter,
				CopyRead,
				CopyWrite,
				DispatchIndirect,
				DrawIndirect,
				/** Index data. */
				ElementArray,
				PixelPack,
				PixelUnpack,
				Query,
				ShaderStorage,
				Texture,
				TransformFeedback,
				RE_LAST(Uniform)
			};

			bool is_available(BufferType type, int gl_major, int gl_minor);

			/** The memory policy of a Buffer. */
			enum class BufferAccess
			{
				Stream,
				Static,
				RE_LAST(Dynamic)
			};

			/** The intention of a Buffer. */
			enum class BufferUsage
			{
				Draw,
				Read,
				RE_LAST(Copy)
			};

			/** Represents an OpenGL buffer object.
				Does not support copy operations. Must be released manually. Allocate / destroy multiple objects at once for more efficiency. */
			class Buffer : Handle
			{	friend class VertexArrayBase;
				static util::Lookup<BufferType, Binding> bindings;

				BufferType m_type;
				BufferAccess m_access;
				BufferUsage m_usage;
			public:
				RECX Buffer(BufferType type, BufferAccess access, BufferUsage usage);
				Buffer(Buffer &&) = default;
				Buffer &operator=(Buffer &&) & = default;

				/** Binds the Buffer. */
				void bind() &;
				/** @return Whether the buffer is currently bound. */
				REIL bool bound() const&;

				/** Allocates the given Buffers.
				None of the given Buffers must be allocated yet. */
				static void alloc(Buffer * const * buffers, size_t count);
				/** Destroys the given Buffers.
				All of the given Buffers must be allocated.
				If the currently bound buffer is destroyed, it becomes unbound. */
				static void destroy(Buffer * const * buffers, size_t count);

				using Handle::exists;
				using Handle::handle;

			protected:
				/** Sets the data stored on the GPU.
				@important The Buffer must exist.
				@param[in] data:
					the data that is to be stored on the GPU.
				@param[in] elements:
					the count of elements in data.
				@param[in] element_size:
					the type size of the elements in data. */
				void data(
					void const* data,
					size_t elements,
					size_t element_size) &;

			private:
				/** Allocates the given Handles as Buffers. */
				static void alloc_handles(
					handle_t * handles,
					size_t count);
				/** Destroys the given Handles as Buffers.
				All of the given Handles must represent an existing Buffer. */
				static void destroy_handles(
					handle_t * handles,
					size_t count);
			};

			template<class Vertex>
			class VertexBuffer : public Buffer
			{
				std::vector<Vertex> m_data;
			public:
				REIL VertexBuffer(
					BufferAccess access,
					BufferUsage usage);
				VertexBuffer(VertexBuffer &&) = default;
				VertexBuffer &operator=(VertexBuffer &&) & = default;

				REIL void data(
					Vertex const * data,
					size_t elements) &;

				REIL void data(
					std::vector<Vertex> data) &;
			};


			class IndexBuffer : public Buffer
			{
				std::vector<index_t> m_data;
			public:
				REIL IndexBuffer(
					BufferAccess access,
					BufferUsage usage);

				REIL void data(
					index_t const * data,
					size_t elements) &;

				REIL void data(
					std::vector<index_t> data) &;
			};
		}
	}
}

#include "Buffer.inl"

#endif
