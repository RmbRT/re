#include "../LogFile.hpp"

namespace re
{
	namespace util
	{
		template<class T>
		NotNull<T>::NotNull(T *data):
			m_data(data)
		{
			RE_DBG_ASSERT(m_data && "Tried to initialize with null!");
		}

		template<class T>
		NotNull<T>::operator T*() const
		{
			return m_data;
		}
	}
}