#include "Handle.hpp"
#include <memory>
namespace re
{
	namespace graphics
	{
		namespace gl
		{
			handle_t * Handle::allocation_buffer(size_t count)
			{
				static std::auto_ptr<handle_t> alloc_buf(nullptr);
				static size_t size = 0;

				if(size < count)
					alloc_buf.reset(
						(handle_t*) realloc(
							alloc_buf.release(),
							(size = count) * sizeof(handle_t)));

				return alloc_buf.get();
			}
		}
	}
}