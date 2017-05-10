#include <type_traits>

#include "../Singleton.hpp"
#include "../LogFile.hpp"

namespace re
{

	void * malloc(size_t size)
	{
		return singleton<util::Heap>().malloc(size);
	}

	void free(void const * mem)
	{
		RE_DBG_ASSERT(mem);

		util::Heap::Header * header = util::Heap::get_header(mem);
		header->m_heap->validate_header(header);
		header->free();
	}

	bool resize(void const * mem, size_t size)
	{
		RE_DBG_ASSERT(mem);
		RE_DBG_ASSERT(size);

		util::Heap::Header * header = util::Heap::get_header(mem);
		header->m_heap->validate_header(header);
		return header->resize(size);
	}

	void * realloc(void const * mem, size_t size)
	{
		if(!mem)
			return malloc(size);
		else
		{
			util::Heap::Header * header = util::Heap::get_header(mem);
			header->m_heap->validate_header(header);
			return header->realloc(size);
		}
	}

	template<class T, class ... Args>
	T * alloc(Args && ... args)
	{
		return singleton<util::Heap>().alloc<T>(
			std::forward<Args>(args)...);
	}

	template<class T>
	T * array_alloc(size_t size)
	{
		return singleton<util::Heap>().array_alloc<T>(size);
	}

	template<class T>
	REIL void dealloc(T * ptr)
	{
		RE_DBG_ASSERT(ptr
			&& "Tried to delete null pointer.");

		ptr->~T();
		free(ptr);
	}

	template<class T>
	REIL void array_dealloc(T * ptr)
	{
		RE_DBG_ASSERT(ptr
			&& "Tried to delete null pointer.");

		util::Heap::Header * const header = util::Heap::get_header(ptr);
		RE_DBG_ASSERT(header->m_heap);
		header->m_heap->validate_header(header);

		RE_DBG_ASSERT(header->m_size % sizeof(T) == 0
			&& "Could not determine array size.");

		size_t const count = header->m_size / sizeof(T);
		for(size_t i = 0; i < count; i++)
			ptr[i].~T();
		free(ptr);
	}

	namespace util
	{
		uintptr_t Heap::end() const
		{
			RE_DBG_ASSERT(exists());
			return uintptr_t(m_pool) + m_capacity;
		}

		bool Heap::is_valid_header_address(Header const * head) const
		{
#ifdef RE_HEAP_DEBUG
			return head
				&& !((uintptr_t(head) - uintptr_t(m_pool)) % sizeof(Header))
				&& (uintptr_t(head) >= uintptr_t(m_pool))
				&& (uintptr_t(head) <= end());
#else
			return true;
#endif
		}

		void Heap::validate_header(Header const * head) const
		{
			#ifdef RE_HEAP_DEBUG
			RE_ASSERT(is_valid_header_address(head));
			RE_ASSERT(head->m_magic == heap_magic);

			if(head->m_prev)
				RE_ASSERT(head->m_prev->m_next == head);
			else
				RE_ASSERT(head == m_first);

			if(head->m_next)
				RE_ASSERT(head->m_next->m_prev == head);
			else
				RE_ASSERT(head == m_last);
			#endif
		}

		RECX Heap::Header * Heap::get_header(void const * membegin)
		{
			return reinterpret_cast<Header*>(uintptr_t(membegin)) - 1;
		}

		template<class T, class ... Args>
		T * Heap::alloc(Args && ... args)
		{
			T * const instance = static_cast<T*>(malloc(sizeof(T)));
			return instance
				? new (instance) T(std::forward<Args>(args)...)
				: nullptr;
		}

		template<class T>
		T * Heap::array_alloc(size_t size)
		{
			T * const array = static_cast<T*>(malloc(sizeof(T) * size));
			return array
				? new (array) T[size]
				: nullptr;
		}

		bool Heap::exists() const
		{
			return m_pool;
		}

		bool Heap::used() const
		{
			return exists() && m_first;
		}

		REIL size_t Heap::Header::capacity() const
		{
			return m_size + hole();
		}

		REIL size_t Heap::Header::hole() const
		{
#ifdef RE_HEAP_DEBUG
			RE_ASSERT(m_next != nullptr && "cannot calculate hole size.");
#endif
			return (uintptr_t)m_next - end();
		}

		REIL uintptr_t Heap::Header::end() const
		{
			return uintptr_t(&this[1]) + m_size;
		}
	}
}