namespace re
{

	void * alloc(size_t size)
	{
		return re::singleton<Heap>().alloc(size);
	}

	void free(void const * mem)
	{
		return re::singleton<Heap>().free(mem);
	}

	bool resize(void const * mem, size_t size)
	{
		return re::singleton<Heap>().resize(mem, size);
	}

	void * realloc(void const * mem, size_t size)
	{
		return re::singleton<Heap>().realloc(mem, size);
	}

	
	namespace util
	{

		RECX size_t

		uintptr_t Heap::end() const
		{
			RE_DBG_ASSERT(exists());
			return uintptr_t(m_pool) + m_size;
		}

		bool Heap::isValidHeaderAddress(Header const * head) const
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

		void Heap::validateHeader(Header const * head) const
		{
			#ifdef RE_HEAP_DEBUG
			RE_ASSERT(isValidHeadAddress(head));
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

		Header * Heap::getHeader(void const * membegin) const
		{
			return static_cast<Header*>(uintptr_t(membegin)) - 1;
		}

		bool Heap::exists() const
		{
			return m_pool;
		}

		bool Heap::used() const
		{
			return exists() && m_first;
		}
	}
}