#include "MultiHeap.hpp"
#include "NotNull.hpp"

namespace re
{
	namespace util
	{
		MultiHeap::MultiHeap(
			size_t heaps,
			size_t size):
			m_heaps(NotNull<Heap>(re::alloc(sizeof(Heap) * heaps))),
			m_count(heaps),
			m_counter(0)
		{
			for(size_t i = 0; i < heaps; i++)
				new (&m_heaps[i]) Heap(size);
		}

		void * MultiHeap::alloc(size_t size)
		{
			size_t const t_counter = m_counter;
			void * ptr;
			while(!(ptr = m_heaps[m_counter++].alloc(size)))
			{
				if(m_counter == m_count)
					m_counter = 0;
				if(m_counter == t_counter)
					return nullptr;
			}

			return ptr;
		}
	}
}