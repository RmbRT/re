#ifndef __re_graphics_gl_handle_hpp_defined
#define __re_graphics_gl_handle_hpp_defined

#include "../../defines.hpp"
#include "../../types.hpp"

namespace re
{
	namespace graphics
	{
		namespace GL
		{
			/** The type used by OpenGL to store object handles. */
			typedef uint handle_t;

			
			/** Represents a handle to a resource managed by OpenGL.
			Does not support copy operations.
			When assigning, the destination Handle must not exist already.
			When a Handle is destroyed, it must not exist anymore. */
			class Handle
			{
				/** The actual OpenGL object handle. */
				handle_t m_handle;
			public:
				/** Creates a Handle that is set to empty. */
				REINL Handle();
				/** Moves the ownership of the handle from one Handle to another. */
				REINL Handle(Handle &&);
				/** Moves the ownership of the handle from one Handle to another. */
				REICXDA Handle &operator=(Handle &&);
				/** Asserts that the Handle must not exist anymore. */
				REICXDA ~Handle();

				/** Use to set the Handle value.
				@important
					The handle must not exist already.
				@param[in] handle:
					The new value of the Handle. */
				REICXDA void set_handle(handle_t handle);
				/** Use to release the Handle value. */
				REICXDA void null_handle();

				/** Returns whether a Handle exists / was allocated. */
				REICX bool exists() const;

				/** Returns the handle to this Handle. */
				REICX handle_t handle() const;
			};
		}
	}
}

#include "Handle.inl"

#endif