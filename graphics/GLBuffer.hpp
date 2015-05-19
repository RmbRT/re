#ifndef __re_glbuffer_hpp_defined
#define __re_glbuffer_hpp_defined

#include "../types.hpp"
#include "AttribLocation.hpp"

namespace re
{
	namespace graphics
	{
		class GLBuffer
		{
			/*The buffer id. This represents the buffer towards the GPU.*/
			uint32 id;
			/*The role of the buffer - position, normal, color or texture coordinate.*/
			AttribLocation location;
		public:
			/*Constructs a new GLBuffer. This does not allocate memory on the GPU.
			@param[in] location:
				The attribute location to store this buffer in.
				@see @{re::graphics::AttribLocation}*/
			explicit GLBuffer(AttribLocation location);

			GLBuffer(GLBuffer &&move);
			GLBuffer &operator=(GLBuffer &&move);

			/*Deletes the GLBuffer. Frees any memory allocated on the GPU for this GLBuffer.*/
			~GLBuffer();

			/*Registers and allocates a buffer id. Call this to allocate memory on the GPU.*/
			void alloc();
			/*Unregisters the buffer id. Call this to delete the memory on the GPU.*/
			void dealloc();
			
			/*Makes the buffer current for use in render calls etc.*/
			void bind();
			/*Binds this buffer as an index buffer.*/
			void indexBind();
			
			/*Unbinds the current bound buffer.*/
			static void unbind();
			
			/*Loads the given data onto the GPU.
			@param[in] elements:
				The count of entries in the data array, not the byte count.
			@param[in] data:
				The data to be stored in the buffer.
			@param[in] usage:
				The usage of the buffer (static, dynamic, etc.)*/
			void data(size_t elements, const void* data, int usage);

			/*Loads the given index data onto the GPU.*/
			void indexData();

			/*Returns the internal id of this GLBuffer.*/
			uint32 getId() const;

		private:
			/*The current bound buffer. This is used to reduce redundant calls to the GPU.*/
			static uint32 bound;
		};
	}
}

#endif