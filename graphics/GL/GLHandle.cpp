#include "GLHandle.hpp"
#include <memory>
namespace re
{
	namespace graphics
	{
		namespace GL
		{
			gl_handle_t * GLHandle::allocation_buffer(size_t count)
			{
				static std::auto_ptr<gl_handle_t> alloc_buf(nullptr);
				static size_t size = 0;

				if(size < count)
					alloc_buf.reset(
						(gl_handle_t*) realloc(
							alloc_buf.release(),
							(size = count) * sizeof(gl_handle_t)));

				return alloc_buf.get();
			}
		}
	}
}