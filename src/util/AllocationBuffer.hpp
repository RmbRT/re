#ifndef __re_util_allocationbuffer_hpp_defined
#define __re_util_allocationbuffer_hpp_defined

#include "../defines.hpp"
#include <vector>

namespace re
{
	namespace util
	{
		namespace detail
		{
			template<class T>
			/** Holds the buffer used by allocation_buffer and free_allocation_buffer. */
			struct AllocationBufferStorage
			{
				static std::vector<T> buffer;
			};
		}

		template<class T>
		/** Returns a reusable Buffer of the given size.
		@param[in] count:
			How many elements to allocate.
		@return
			The allocated buffer.
		@important The returned buffer is invalidated after the next call to allocation_buffer. */
		T * allocation_buffer(size_t count);

		template<class T>
		/** For manually releasing the memory held by AllocationBufferStorage<T>::buffer.
			This function is optional.
		@side Frees the memory held by AllocationBufferStorage<T>::buffer. */
		void free_allocation_buffer();
	}
}

#include "AllocationBuffer.inl"

#endif