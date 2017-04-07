#include "../LogFile.hpp"

namespace re
{
	namespace util
	{
		/*template<class T>
		RECXDA NotNull<T>::NotNull(T *data):
			m_data(data)
		{
			RE_DBG_ASSERT(m_data
				&& "Tried to initialize with null!");
		}*/

		template<class T>
		RECXDA NotNull<T>::NotNull(T * data):
			m_data(data)
		{
			RE_DBG_ASSERT(m_data
				&& "Tried to initialize with null!");
		}

		template<class T>
		template<class X>
		RECXDA NotNull<T>::NotNull(X * data):
			NotNull((T*) data)
		{
		}

		template<class T>
		RECXDA NotNull<T>::operator T*() const
		{
			return m_data;
		}

		template<class T>
		RECXDA T * NotNull<T>::operator->() const
		{
			return m_data;
		}

		template<class T>
		RECXDA T & NotNull<T>::operator*() const
		{
			return *m_data;
		}

		template<class T>
		template<class X>
		RECXDA NotNull<T>::operator typename std::enable_if<
			std::is_convertible<T *, X *>::value,
			X *>::type () const
		{
			return NotNull<X *>(m_data);
		}

		template<class T>
		RECXDA NotNull<T> notNull(T * data)
		{
			return data;
		}

		template<class To, class From>
		RECXDA NotNull<To> reinterpret(NotNull<From> data)
		{
			return reinterpret_cast<To *>((From*)data);
		}
	}
}