#ifndef __re_graphics_gl_renderbuffer_hpp_defined
#define __re_graphics_gl_renderbuffer_hpp_defined

#include "../../defines.hpp"
#include "Handle.hpp"
#include "Binding.hpp"

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			/** An OpenGL render buffer.
				Does not support copying, and must be manually allocated and destroyed. Cluster multiple objects into an allocation / destruction call to get optimal performance. */
			class RenderBuffer : Handle
			{
				/** The currently bound render buffer.
					This is used to reduce the overhead of the `bind()` and `unbind()` functions. */
				static Binding s_bound;

				/** The width of the render buffer. */
				uint32_t m_width;
				/** The height of the render buffer. */
				uint32_t m_height;
			public:
				/** Creates an unallocated render buffer. */
				RenderBuffer() = default;
				RenderBuffer(RenderBuffer &&) = default;
				RenderBuffer &operator=(RenderBuffer &&) = default;

				RenderBuffer(RenderBuffer const&) = delete;
				RenderBuffer &operator=(RenderBuffer const&) = delete;

				/** Allocates render buffers.
					Group as many objects as possible into every call to reduce overhead.
				@assert
					The objects must not exist.
				@param[in] objects:
					The render buffers to allocate.
				@param[in] count:
					The number of render buffers. */
				static void alloc(
					RenderBuffer * const * objects,
					size_t count);
				/** Destroys render buffers.
					Group as many objects as possible into every call to reduce overhead.
				@assert
					The objects must exist.
				@param[in] objects:
					The render buffers to destroy.
				@param[in] count:
					The number of render buffers. */
				static void destroy(
					RenderBuffer * const * objects,
					size_t count);

				/** Resizes the render buffer.
				@assert
					The render buffer must exist.
				@param[in] width:
					The new width of the render buffer.
				@param[in] height:
					The new height of the render buffer. */
				void resize(
					uint32_t width,
					uint32_t height);

				/** Retrieves the render buffer's width.
				@assert
					The render buffer must exist. */
				REIL uint32_t width() const;
				/** Retrieves the render buffer's height.
				@assert
					The render buffer must exist. */
				REIL uint32_t height() const;

				using Handle::handle;
				using Handle::exists;

				REIL bool bound() const;

				/** Binds the render buffer for further calls.
				@assert
					The render buffer must exist. */
				void bind();
				/** Unbinds the currently bound render buffer, if any. */
				static void unbind();
			};
		}
	}
}

#include "RenderBuffer.inl"

#endif