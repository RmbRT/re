#include <type_traits>

namespace re
{
	namespace util
	{
		template<class T>
		RECX14 T &RefCount<T>::get()
		{
			return m_instance;
		}

		template<class T>
		RECX T const& RefCount<T>::get() const
		{
			return m_instance;
		}

		template<class T>
		RECX size_t RefCount<T>::count() const
		{
			return m_count;
		}

		template<class T>
		REIL void RefCount<T>::reference()
		{
			++m_count;
		}

		template<class T>
		REIL size_t RefCount<T>::unreference()
		{
			return --m_count;
		}

		template<class T>
		template<class ...Args>
		REIL RefCount<T>::RefCount(Args && ... args):
			m_count(0),
			m_instance(std::forward<Args>(args)...)
		{
		}
	}
}