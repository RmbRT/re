namespace re
{
	namespace util
	{
		template<class T>
		Shared<T>::Shared() :
			m_obj(nullptr)
		{
		}

		template<class T>
		Shared<T>::Shared(nullptr_t):
			m_obj(nullptr)
		{
		}

		template<class T>
		Shared<T>::Shared(RefCount<T> & ref):
			m_obj(&ref)
		{
			ref.reference();
		}

		template<class T>
		Shared<T>::Shared(Shared<T> const& copy):
			m_obj(copy.m_obj)
		{
			if(m_obj)
				m_obj->reference();
		}

		template<class T>
		Shared<T>::Shared(Shared<T> && move):
			m_obj(copy.m_obj)
		{
			copy.m_obj = nullptr;
		}

		template<class T>
		Shared<T> &Shared<T>::operator=(Shared<T> const& copy)
		{
			if(this != &copy && m_obj != copy.m_obj)
			{
				unref();
				m_obj = copy.m_obj;
				if(m_obj)
					m_obj->reference();
			}

			return *this;
		}

		template<class T>
		Shared<T> &Shared<T>::operator=(Shared<T> && move)
		{
			if(this != &move)
			{
				unref();
				m_obj = move.m_obj;
			}

			return *this;
		}

		template<class T>
		Shared<T>::unref()
		{
			if(m_obj)
			{
				m_obj->unreference();
				if(!m_obj->count())
					m_obj->~T(),
					re::free(m_obj);
			}
		}

		template<class T>
		Shared<T>::~Shared()
		{
			unref();
		}

		template<class T>
		Shared<T>::operator T*() const
		{
			return m_obj ? m_obj->get() : nullptr;
		}

		template<class T>
		template<class ...Args>
		Shared<T> Shared<T>::alloc(Args && ... args)
		{
			return *(new RefCount<T>(std::forward<Args>(args)...));
		}

		template<class T>
		Auto<T>::Auto():
			m_obj(nullptr)
		{
		}

		template<class T>
		Auto<T>::Auto(Auto<T> && move):
			m_obj(move.m_obj)
		{
			move.m_obj = nullptr;
		}

		template<class T>
		Auto<T> &Auto<T>::operator=(Auto<T> && move)
		{
			if(this != &move)
			{
				delete move;
			}
			return *this;
		}
	}
}