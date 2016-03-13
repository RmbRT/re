#ifndef __re_graphics_gl_glhandle_hpp_defined
#define __re_graphics_gl_glhandle_hpp_defined

#include "../../defines.hpp"
#include "../../types.hpp"

namespace re
{
	namespace graphics
	{
		namespace GL
		{
			/* The type used by OpenGL to store object handles. */
			typedef uint32 gl_handle_t;

			
			/* Represents a handle to a resource managed by OpenGL.
			Does not support copy operations.
			When assigning, the destination GLHandle must not exist already.
			When a GLHandle is destroyed, it must not exist anymore. */
			class GLHandle
			{
				/* The OpenGL object handle to this GLHandle. */
				gl_handle_t m_gl_handle;
			public:
				/* Creates a GLHandle that is set to empty. */
				REINL GLHandle();
				/* Moves the ownership of the handle from one GLHandle to another. */
				REINL GLHandle(GLHandle &&);
				/* Moves the ownership of the handle from one GLHandle to another. */
				REINL GLHandle &operator=(GLHandle &&);
				/* Asserts that the GLHandle must not exist anymore. */
				REINL ~GLHandle();
				
				GLHandle(GLHandle const&) = delete;
				GLHandle &operator=(GLHandle const&) = delete;

				/* Use to set the GLHandle value. The handle must not exist already.
				@param[in] gl_handle: the new value of the GLHandle. */
				REINL void set_gl_handle(gl_handle_t gl_handle);
				/* Use to release the GLHandle value. */
				REINL void null_gl_handle();

				/* Returns whether a GLHandle exists / was allocated. */
				REINL bool exists() const;

				/* Returns the handle to this GLHandle. */
				REINL gl_handle_t gl_handle() const;

				static gl_handle_t * allocation_buffer(size_t count);
			};
		}
	}
}

#include "GLHandle.inl"

#endif