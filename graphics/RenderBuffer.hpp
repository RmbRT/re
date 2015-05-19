#ifndef __re_renderbuffer_hpp_defined
#define __re_renderbuffer_hpp_defined

#include "../types.hpp"
#include "../defines.hpp"

namespace re
{
	namespace graphics
	{
		RE_ENUM(RenderBufferType)
		{
			BUFFER_DEPTH,
			BUFFER_STENCIL,
			BUFFER_DEPTH_STENCIL
		};

		class RenderBuffer
		{
			/*The handle of the RenderBuffer.*/
			uint32 id;
			/*To reduce GPU calls, store width and height.*/
			uint32 width, height;
		public:
			/*Creates a RenderBuffer. This does not allocate memory on the GPU!*/
			RenderBuffer();

			/*Moves a RenderBuffer and invalidates the old one.*/
			RenderBuffer(RenderBuffer &&move);

			/*Desroys the RenderBuffer. This deallocates all the memory used on the GPU by it.*/
			~RenderBuffer();
			/*Call this to allocate memory on the GPU.*/
			void alloc();
			/*Call this to delete the memory on the GPU.*/
			void destroy();

			/*Resizes the RenderBuffer on the GPU.*/
			void setSize(uint32 width, uint32 height);
			/*Returns the width of the RenderBuffer. The value is fetched from the GPU.*/
			uint32 getWidth() const;
			/*Returns the height of the RenderBuffer. The value is fetched from the GPU.*/
			uint32 getHeight() const;
			/*Returns the id of the RenderBuffer.*/
			uint32 getId() const;

			/*Used to bind the RenderBuffer to the GPU.*/
			void bind() const;
			/*Checks whether the id is already bound.*/
			bool isBound() const;

			/*Unbinds the current bound Buffer.*/
			static void unbind();
		private:
			static uint32 bound;
		};
	}
}

#endif