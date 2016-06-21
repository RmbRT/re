#ifndef __re_util_multiheap_hpp_defined
#define __re_util_multiheap_hpp_defined

#include "../defines.hpp"

#include "Pointer.hpp"
#include "Heap.hpp"

namespace re
{
	namespace util
	{
		/** Structure for distributing allocations to multiple heaps, which should generally speed up the process of finding a hole. */
		class MultiHeap
		{
			Auto<Heap[]> m_heaps;
			size_t m_count;
			size_t m_counter;

		public:
			/** Constructs a split heap.
			@param[in] heaps:
				The heap count.
			@param[in] size:
				The individual heap size. */
			MultiHeap(size_t heaps, size_t size);
			~MultiHeap();

			/** Allocates */
			void * malloc(size_t size);

			template<class T, class ... Args>
			REIL T * alloc(Args && ... args);

			template<class T>
			REIL T * array_alloc(size_t size);
		};
	}
}

#endif