namespace re
{
	template<class C>
	RECX String<C>::String():
		m_data(nullptr),
		m_size(0),
		m_capacity(0)
	{
	}

	namespace detail
	{
		template<class C>
		size_t strlen(NotNull<C const> ptr)
		{
			size_t len = 0;
			while(*ptr++)
				++len;
			return len;
		}
	}

	template<class C>
	String<C>::String(NotNull<C const> ptr):
		m_data(nullptr),
		m_size(0),
		m_capacity(0)
	{
		resize(detail::strlen(ptr));
		for(size_t i = m_size; i--;)
			m_data[i] = ptr[i];
	}

	template<class C>
	REIL void String<C>::resize(size_t size)
	{
		if(capacity() < size)
			// reserve.
			reserve(size+1);
		
		if(this->size() < size)
		{	// grow.
			m_data[m_size] = '\0';
			m_size = size;
		} else
		{	// shrink.
			m_data[m_size = size] = '\0';
		}
	}
}