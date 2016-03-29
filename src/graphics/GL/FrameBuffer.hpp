#ifndef __re_graphics_gl_framebuffer_hpp_defined
#define __re_graphics_gl_framebuffer_hpp_defined

#include "../../defines.hpp"
#include "../../types.hpp"
#include "Handle.hpp"
#include "RenderBuffer.hpp"
#include "Texture.hpp"

#include "../../math/Vector.hpp"

namespace re
{
	namespace graphics
	{
		namespace GL
		{
			/** Represents an OpenGL FrameBuffer object. */
			class FrameBuffer : Handle
			{
				/** The FrameBuffer currently used for read operations. */
				static Binding bound_read;
				/** The FrameBuffer currently used for write operations. */
				static Binding bound_write;
				
				/**@{
					The bounds of the FrameBuffer. */
				uint32
					m_width,
					m_height;
				/**@}*/

				/**@{
					The attachments of the FrameBuffer. */
				Texture2D m_color;
				RenderBuffer m_depth;
				RenderBuffer m_stencil;
				RenderBuffer m_depth_stencil;
				/**@}*/
				
			public:
				/** Creates an empty FrameBuffer Handle. */
				FrameBuffer();
				FrameBuffer(FrameBuffer &&) = default;
				FrameBuffer & operator=(FrameBuffer &&) = default;

				/** Binds this FrameBuffer for read operations. */
				void bind_read() &;
				/** Binds this FrameBuffer for write operations. */
				void bind_write() &;
				/** Binds this FrameBuffer for read and write operations.
					This function is to be preferred instead of calling bind_read and bind_write. */
				void bind_both() &;

				/** Unbinds the currently bound read FrameBuffer. */
				static void unbind_read();
				/** Unbinds the currently bound write FrameBuffer. */
				static void unbind_write();
				/** Unbinds all currently bound FrameBuffers. */
				static void unbind_both();

				/** Allocates the given FrameBuffers.
				@important: None of the given FrameBuffers must exist.
				@param[in] objects: The FrameBuffers to allocate.
				@param[in] count: The count of the FrameBuffers. */
				static void alloc(FrameBuffer * objects, size_t count);
				/** Destroys the given FrameBuffers.
				@important: All of the given FrameBuffers must exist.
				@param[in] objects: The FrameBuffers to destroy.
				@param[in] count: The count of the FrameBuffers. */
				static void destroy(FrameBuffer * objects, size_t count);

				/** buffer = null to use default (= window) buffer. */
				static void blit(
					FrameBuffer * source,
					FrameBuffer * dest,
					math::uivec2 const& src_origin,
					math::uivec2 const& src_end,
					math::uivec2 const& dst_origin,
					math::uivec2 const& dst_end,
					bool blit_color,
					bool blit_depth,
					bool blit_stencil,
					bool interpolate);

				void attach_color(Texture && color) &;
				void detach_color(Texture & out);
				REINL bool has_color() const;

				void attach_depth(RenderBuffer && depth) &;
				void detach_depth(RenderBuffer & out);
				REINL bool has_depth() const;

				void attach_stencil(RenderBuffer && stencil) &;
				void detach_stencil(RenderBuffer & out);
				REINL bool has_stencil() const;

				void attach_depth_stencil(RenderBuffer && depth_stencil) &;
				void detach_depth_stencil(RenderBuffer & out);
				REINL bool has_depth_stencil() const;

				/** Resizes the FrameBuffer and all its attachments to the given size. */
				void resize(uint32 width, uint32 height) &;
			};
		}
	}
}

#include "FrameBuffer.inl"

#endif