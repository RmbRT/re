#include "../LogFile.hpp"

namespace re
{
	namespace util
	{
		template<class T>
		RECXDA NotNull<T>::NotNull(T *data):
			m_data(data)
		{
			RE_DBG_ASSERT(m_data
				&& "Tried to initialize with null!");
		}

		template<class T>
		RECX NotNull<T>::operator T*() const
		{
			return m_data;
		}

		template<class T>
		RECX T * NotNull<T>::operator->() const
		{
			return m_data;
		}

		template<class T>
		RECX T & NotNull<T>::operator*() const
		{
			return *m_data;
		}

		template<class T>
		RECX NotNull<T> notNull(T * data)
		{
			return data;
		}
	}
}