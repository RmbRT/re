namespace re
{
	template<class C>
	RECX String<C>::String():
		m_ptr(nullptr),
		m_size(0),
		m_capacity(0)
	{
	}
}