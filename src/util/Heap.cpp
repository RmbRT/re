#include "Heap.hpp"
#include "Error.hpp"

#include <memory>
#include <cstring>

namespace re
{
	namespace util
	{
		Heap::Heap():
			m_pool(0),
			m_capacity(0),
			m_first(nullptr),
			m_last(nullptr)
		{
		}


		Heap::Heap(size_t capacity) :
			m_pool(0),
			m_capacity(0),
			m_first(nullptr),
			m_last(nullptr)
		{
			create(capacity);
		}

		Heap::Heap(Heap && move) :
			m_pool(move.m_pool),
			m_capacity(move.m_capacity),
			m_first(move.m_first),
			m_last(move.m_last)
		{
			move.invalidate();
		}

		Heap &Heap::operator=(Heap && move)
		{
			if(this == &move)
				return * this;

			dealloc();

			*this = (Heap const&) move;
			move.invalidate();
		}

		Heap::~Heap()
		{
			dealloc();
		}

		void * Heap::malloc(size_t size)
		{
			RE_DBG_ASSERT(exists()
				&& "heap is not allocated");

			if(size_t const rest = size % sizeof(Header))
				size += sizeof(Header) - rest;

			size_t const hole_needed = size + sizeof(Header);

			if(!m_first)
			{	// empty heap?
				if(m_capacity < hole_needed)
					return nullptr;

				m_first = m_pool;
#ifdef RE_HEAP_DEBUG
				// set the magic number.
				m_first->m_magic = heap_magic;
#endif
				m_first->m_next = nullptr;
				m_first->m_size = size;
				m_first->m_heap = this;
				m_first->m_prev = nullptr;

				m_last = m_first;

				validate_header(m_first);

				// return the address after the header.
				return m_first+1;
			}

			if(uintptr_t(m_first) - uintptr_t(m_pool+1) >= hole_needed)
			{	// gap at the beginning?
				validate_header(m_first);

				m_pool->m_next = m_first;
				m_first->m_prev = m_pool;
				m_first = m_pool;
				m_first->m_heap = this;
#ifdef RE_HEAP_DEBUG
				m_first->m_magic = heap_magic;
#endif
				m_first->m_size = size;

				validate_header(m_first);
				return m_first+1;
			}

			if(end() - m_last->end() >= hole_needed)
			{	// gap at end?
				Header * const header = reinterpret_cast<Header*>(m_last->end());

#ifdef RE_HEAP_DEBUG
				header->m_magic = heap_magic;
#endif
				header->m_prev = m_last;
				header->m_heap = this;
				header->m_size = size;
				header->m_next = nullptr;

				m_last->m_next = header;
				m_last = header;

				validate_header(header);

				return header + 1;
			} else if(!m_last->m_prev)
			{	// only one node, but still not enough room?
				return nullptr;
			}

			// these are the two iterators, as we will try to find a hole starting from both ends.
			struct { Header * m_header; int const m_next; } iterators[] = {
				{ m_first, 1 },
				{ m_last->m_prev, 0 }
			}, * it = iterators;

			while(it->m_header && it->m_header->m_next)
			{
				validate_header(it->m_header);

				if(it->m_header->hole() >= hole_needed)
				{	// found a satisfying hole?
					Header * const header = reinterpret_cast<Header *>(it->m_header->end());
					header->m_prev = it->m_header;
					header->m_heap = this;
					header->m_next = it->m_header->m_next;
					it->m_header->m_next = header;
					header->m_next->m_prev = header;
					it->m_header->m_size = size;
#ifdef RE_HEAP_DEBUG
					header->m_magic = heap_magic;
#endif

					validate_header(header);
					return header + 1;
				}

				// not found, iterate.
				if(it->m_next)
					it->m_header = it->m_header->m_next;
				else
					it->m_header = it->m_header->m_prev;

				it = &iterators[it->m_next];
			}

			return nullptr;
		}

		bool Heap::Header::resize(size_t size)
		{
			RE_DBG_ASSERT(m_heap);
			m_heap->validate_header(this);

			if(this == m_heap->m_last)
			{
				uintptr_t mem = uintptr_t(this + 1);
				uintptr_t end = m_heap->end();

				if(end-mem >= size)
				{
					m_size = size;
					return true;
				}
			} else if(capacity() >= size)
			{
				m_size = size;
				return true;
			}

			return false;
		}

		void * Heap::Header::realloc(size_t size)
		{
			RE_DBG_ASSERT(m_heap);
			m_heap->validate_header(this);

			if(resize(size))
				return this + 1;

			void * const moved = m_heap->malloc(size);
			std::memcpy(moved, this + 1, m_size);
			free();
			return moved;
		}

		void Heap::Header::free()
		{
			RE_DBG_ASSERT(m_heap);
			m_heap->validate_header(this);

			if(m_prev)
				m_prev->m_next = m_next;
			else
				m_heap->m_first = m_next;

			if(m_next)
				m_next->m_prev = m_prev;
			else
				m_heap->m_last = m_prev;
		}

		void Heap::create(size_t capacity)
		{
			/** capacity must be multiple of sizeof(Header). */
			if(capacity & (sizeof(Header)-1))
				capacity = (capacity + sizeof(Header)) & ~(sizeof(Header)-1);

			RE_DBG_ASSERT(!exists()
				&& "Tried to allocate heap that is already allocated.");

			RE_FATAL_LOG(
				m_pool = static_cast<Header *>(std::malloc(capacity)),
				"util::Heap allocation"
			);

			m_capacity = capacity;
			m_first = nullptr;
			m_last = nullptr;
		}

		void Heap::dealloc()
		{
			if(exists())
			{
				RE_DBG_ASSERT(!used()
					&& "Tried to dealloc heap that is still used.");

				std::free(static_cast<void*>(m_pool));
				invalidate();
			}
		}

		void Heap::invalidate()
		{
			m_pool = 0;
		}
	}
}