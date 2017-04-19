namespace re
{
	namespace util
	{
		template<class T>
		RECX Shared<T>::Shared() :
			m_obj(nullptr)
		{
		}

		template<class T>
		RECX Shared<T>::Shared(nullptr_t):
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
			m_obj(move.m_obj)
		{
			move.m_obj = nullptr;
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
		void Shared<T>::unref()
		{
			if(m_obj)
			{
				if(!m_obj->unreference())
				{
					m_obj->get().~T();
					re::free(m_obj);
				}
			}
		}

		template<class T>
		Shared<T>::~Shared()
		{
			unref();
		}

		template<class T>
		T* Shared<T>::operator->() const
		{
			return m_obj ? &m_obj->get() : nullptr;
		}

		template<class T>
		T& Shared<T>::operator*() const
		{
			RE_DBG_ASSERT(m_obj != nullptr);
			return m_obj->get();
		}

		template<class T>
		template<class ...Args>
		Shared<T> Shared<T>::alloc(Args && ... args)
		{
			return *(new RefCount<T>(std::forward<Args>(args)...));
		}

		template<class T>
		RECX Shared<T>::operator bool() const
		{
			return m_obj != nullptr;
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
			RE_DBG_ASSERT(&move != this
				&& "tried to move to self.");

			if(m_obj)
				dealloc(m_obj);
			m_obj = move.m_obj;
			move.m_obj = nullptr;

			return *this;
		}

		template<class T>
		Auto<T> &Auto<T>::operator=(T * ptr)
		{
			RE_DBG_ASSERT(!m_obj || m_obj != ptr
				&& "cannot reassign the same pointer value!");

			if(m_obj)
				dealloc(m_obj);
			m_obj = ptr;

			return *this;
		}

		template<class T>
		Auto<T>::Auto(T * ptr):
			m_obj(ptr)
		{
		}

		template<class T>
		Auto<T>::~Auto()
		{
			if(m_obj)
				dealloc(m_obj);
		}

		template<class T>
		Auto<T>::operator bool() const
		{
			return m_obj != nullptr;
		}

		template<class T>
		T * Auto<T>::release()
		{
			T * value = m_obj;
			m_obj = nullptr;
			return value;
		}

		template<class T>
		T* Auto<T>::operator->() const
		{
			return m_obj;
		}

		template<class T>
		Auto<T[]>::Auto(T * ptr):
			Auto<T>(ptr)
		{
		}

		template<class T>
		Auto<T []> &Auto<T []>::operator=(Auto<T []> && move)
		{
			RE_DBG_ASSERT(&move != this
				&& "tried to move to self.");

			if(this->m_obj)
				array_dealloc(this->m_obj);

			this->m_obj = move.m_obj;
			move.m_obj = nullptr;

			return *this;
		}

		template<class T>
		Auto<T []> &Auto<T []>::operator=(T * ptr)
		{
			RE_DBG_ASSERT(!m_obj || m_obj != ptr
				&& "cannot reassign the same pointer value!");

			if(this->m_obj)
				array_dealloc(this->m_obj);

			this->m_obj = ptr;

			return *this;
		}

		template<class T>
		Auto<T[]>::~Auto()
		{
			if(this->m_obj)
			{
				array_dealloc(this->m_obj);
				this->m_obj = nullptr;
			}
		}

		template<class T>
		REIL T const& Auto<T []>::operator[](size_t i) const
		{
			RE_DBG_ASSERT(m_obj != nullptr);
			return m_obj[i];
		}
		template<class T>
		REIL T &Auto<T []>::operator[](size_t i)
		{
			RE_DBG_ASSERT(m_obj != nullptr);
			return m_obj[i];
		}
	}
}