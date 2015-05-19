#ifndef __re_framebuffer_hpp_defined
#define __re_framebuffer_hpp_defined

#include "../defines.hpp"
#include "../types.hpp"
#include "Texture.hpp"
#include "RenderBuffer.hpp"
#include "VertexData.hpp"

namespace re
{
	namespace graphics
	{
		class FrameBuffer
		{
			uint32 id;
			uint32 width, height;
			Texture bufferColor;
			RenderBuffer bufferDepth;
			RenderBuffer bufferStencil;
			RenderBuffer bufferDepthStencil;
		public:
			/*Constructs a FrameBuffer with default values. This does not allocate memory on the GPU!*/
			FrameBuffer();
			/**/
			FrameBuffer(FrameBuffer &&move);
			/*Destroys the FrameBuffer and deletes the memory on the GPU.
			The Render Buffers attached will also be destroyed.*/
			~FrameBuffer();

			/*Call this to allocate the FrameBuffer on the GPU.
			This does not allocate the RenderBuffers.*/
			void alloc();
			/*Call this to release the memory on the GPU. The Render Buffers attached will also be destroyed.*/
			void destroy();

			/*Resizes the FrameBuffer and its Buffers.
			@asserts: FrameBuffer must be allocated.*/
			void setSize(uint32 width, uint32 height);
			/*Returns the width of the FrameBuffer. If it does not exist, returns 0.*/
			uint32 getWidth() const;
			/*Returns the height of the FrameBuffer. If it does not exist, returns 0.*/
			uint32 getHeight() const;

			/*Returns the Color buffer of the FrameBuffer.*/
			const Texture &getBufferColor() const;
			/*Returns the Color buffer of the FrameBuffer.*/
			Texture &getBufferColor();
			/*Returns the Depth buffer of the FrameBuffer.*/
			const RenderBuffer &getBufferDepth() const;
			/*Returns the Depth buffer of the FrameBuffer.*/
			RenderBuffer &getBufferDepth();
			/*Returns the Stencil buffer of the FrameBuffer.*/
			const RenderBuffer &getBufferStencil() const;
			/*Returns the Stencil buffer of the FrameBuffer.*/
			RenderBuffer &getBufferStencil();
			/*Returns the Depth Stencil buffer of the FrameBuffer.*/
			const RenderBuffer &getBufferDepthStencil() const;
			/*Returns the Depth Stencil buffer of the FrameBuffer.*/
			RenderBuffer &getBufferDepthStencil();

			/*Creates the Color Buffer and attaches it to the FrameBuffer.
			This function does nothing if it is already attached.*/
			void attachBufferColor(void);
			/*Checks whether the Color Buffer exists and is attached.*/
			bool hasBufferColor(void) const;
			/*Detaches the Color Buffer and destroys it.*/
			void detachBufferColor(void);

			/*Creates the Depth Buffer and attaches it to the FrameBuffer.
			This function does nothing if it is already attached.*/
			void attachBufferDepth(void);
			/*Checks whether the Depth Buffer exists and is attached.*/
			bool hasBufferDepth(void) const;
			/*Detaches the Depth Buffer and destroys it.*/
			void detachBufferDepth(void);

			/*Creates the Stencil Buffer and attaches it to the FrameBuffer.
			This function does nothing if it is already attached.*/
			void attachBufferStencil(void);
			/*Checks whether the Stencil Buffer exists and is attached.*/
			bool hasBufferStencil(void) const;
			/*Detaches the Stencil Buffer and destroys it.*/
			void detachBufferStencil(void);

			/*Creates the Depth Stencil Buffer and attaches it to the FrameBuffer.
			This function does nothing if it is already attached.*/
			void attachBufferDepthStencil(void);
			/*Checks whether the Depth Stencil Buffer exists and is attached.*/
			bool hasBufferDepthStencil(void) const;
			/*Detaches the Depth Stencil Buffer and destroys it.*/
			void detachBufferDepthStencil(void);

			/*Fetches from the GPU whether the FrameBuffer still exists.*/
			bool exists() const;
			/*Binds the FrameBuffer to redirect rendering towards it.*/
			void bind();
			/*Checks whether the FrameBuffer is currently bound.*/
			bool isBound() const;

			/*Unbinds the currently bound FrameBuffer.*/
			static void unbind();

		private:
			static uint32 bound;
		};
	}
}

#endif