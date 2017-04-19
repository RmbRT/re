namespace re
{
	template<class C>
	C const String<C>::s_empty = (C) '\0';

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
		size_t strlen(
			C const * ptr)
		{
			size_t len = 0;
			while(*ptr++)
				++len;
			return len;
		}
	}

	template<class C>
	String<C>::String(
		C const * ptr):
		m_data(nullptr),
		m_size(0),
		m_capacity(0)
	{
		resize(detail::strlen(ptr));
		for(size_t i = m_size; i--;)
			m_data[i] = ptr[i];
	}

	template<class C>
	String<C>::String(
		String<C> const& copy):
		String(copy.m_data.operator->())
	{
	}

	template<class C>
	String<C>::String(
		String<C> && move):
		m_data(std::move(move.m_data)),
		m_size(move.m_size),
		m_capacity(move.m_capacity)
	{
		move.m_size = 0;
		move.m_capacity = 0;
	}

	template<class C>
	String<C> &String<C>::operator=(
		C const * ptr)
	{
		resize(detail::strlen(ptr));
		for(size_t i = m_size; i--;)
			m_data[i] = ptr[i];
	}

	/*
	template<class C>
	typename std::enable_if<
		!std::is_same<C, typename String<C>::stdchar_t>::value,
		String<C>>::type &String<C>::operator=(
		typename String<C>::stdchar_t const * ptr)
	{
		return *this = reinterpret_cast<C const>& *(ptr);
	} */

	template<class C>
	String<C> &String<C>::operator=(
		String<C> const& copy)
	{
		*this = copy.m_data;
	}

	template<class C>
	String<C> &String<C>::operator=(
		String<C> && move)
	{
		RE_DBG_ASSERT(this != &move);
		m_data = std::move(move.m_data);
		m_size = move.m_size;
		m_capacity = move.m_capacity;

		move.m_size = 0;
		move.m_capacity = 0;
	}

	template<class C>
	bool String<C>::operator==(
		String<C> const& rhs) const
	{
		if(rhs.empty())
			return empty();
		if(m_size != rhs.m_size)
			return false;

		return *this == rhs.m_data;
	}

	template<class C>
	bool String<C>::operator==(
		C const * rhs) const
	{
		if(!m_size)
			return *rhs == (C) '\0';

		for(size_t i = 0; i<m_size; i++)
			if(rhs[i] != m_data[i])
				return false;

		return !rhs[m_size];
	}

	/*
	template<class C>
	REIL bool String<C>::operator==(
			typename String<C>::stdchar_t const * rhs) const
	{
		return *this == (C const *) rhs;
	}*/

	template<class C>
	String<C> &String<C>::operator+=(
			C const * rhs)
	{
		append(rhs);
		return *this;
	}

	template<class C>
	String<C> &String<C>::operator+=(
			String<C> const& rhs)
	{
		append(rhs.data(), rhs.size());
		return *this;
	}

	template<class C>
	bool String<C>::empty() const
	{
		return !m_size;
	}

	template<class C>
	size_t String<C>::size() const
	{
		return m_size;
	}

	template<class C>
	size_t String<C>::length() const
	{
		RE_ASSERT("not implemented");
	}

	template<class C>
	C const * String<C>::data() const
	{
		return m_data.operator->();
	}

	template<class C>
	C * String<C>::data()
	{
		return m_data;
	}

	template<class C>
	REIL typename String<C>::stdchar_t const * String<C>::c_str() const
	{
		return empty()
			? ""
			: reinterpret_cast<
					typename detail::to_std_char<C>::type const *>(m_data.operator->());
	}

	template<class C>
	C const * String<C>::content() const
	{
		return empty()
			? &s_empty
			: m_data.operator->();
	}

	template<class C>
	size_t String<C>::capacity() const
	{
		return m_capacity;
	}

	template<class C>
	REIL void String<C>::reserve(
		size_t capacity)
	{
		if(m_capacity < capacity)
		{
			m_data = (C*)realloc(
				m_data.release(),
				sizeof(C) * (capacity + 1));
			m_capacity = capacity;
		}
	}

	template<class C>
	REIL void String<C>::resize(
		size_t size)
	{
		if(capacity() < size)
			reserve(size + 1);

		if(this->size() < size)
		{	// grow.
			m_data[m_size] = '\0';
			m_size = size;
		} else
		{	// shrink.
			m_data[m_size = size] = '\0';
		}
	}

	template<class C>
	REIL void String<C>::clear()
	{
		m_data = nullptr;
		m_size = 0;
		m_capacity = 0;
	}

	template<class C>
	REIL void String<C>::append(
		C const * other)
	{
		append(other, detail::strlen(other));
	}

	template<class C>
	void String<C>::append(
		C const * other,
		size_t length)
	{
		size_t end = m_size;
		resize(m_size + length);

		for(size_t i = length; i--;)
			m_data[end + i] = other[i];
	}
}