#include <type_traits>

namespace re
{
	namespace util
	{
		template<class T>
		T &RefCount<T>::get()
		{
			return m_instance;
		}

		template<class T>
		T const& RefCount<T>::get() const
		{
			return m_instance;
		}

		template<class T>
		size_t RefCount<T>::count() const
		{
			return m_count;
		}

		template<class T>
		void RefCount<T>::reference()
		{
			++m_count;
		}

		template<class T>
		void RefCount<T>::unreference()
		{
			return --m_count;
		}

		template<class T>
		template<class ...Args>
		RefCount<T>::Refcount(Args && ... args):
			m_count(0),
			m_instance(std::forward<Args>(args)...)
		{
		}
	}
}