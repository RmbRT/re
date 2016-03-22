#include "../LogFile.hpp"

namespace re
{
	namespace util
	{
		template<class T>
		notnull<T>::notnull(T *data):
			m_data(data)
		{
			RE_DBG_ASSERT(m_data && "Tried to initialize with null!");
		}

		template<class T>
		notnull<T>::operator T*() const
		{
			return m_data;
		}
	}
}