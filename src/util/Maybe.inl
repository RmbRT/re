namespace re
{
	namespace util
	{
		template<class T>
		Maybe<T>::Maybe():
			set(false),
			value()
		{
		}

		template<class T>
		Maybe<T>::Maybe(T const& value):
			set(true),
			value(value)
		{
		}

		template<class T>
		Maybe<T>::operator bool () const
		{
			return set;
		}

		template<class T>
		T& Maybe<T>::operator*()
		{
			return value;
		}

		template<class T>
		T const& Maybe<T>::operator*() const
		{
			return value;
		}

		template<class T>
		T const& Maybe<T>::operator() (T const& default_val) const
		{
			return set ? value : default_val;
		}
	}
}