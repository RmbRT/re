namespace re
{
	namespace util
	{
		template<class T>
		RECX Maybe<T>::Maybe():
			set(false),
			value()
		{
		}

		template<class T>
		RECX Maybe<T>::Maybe(copy_arg_t<T> value):
			set(true),
			value(value)
		{
		}

		template<class T>
		RECX Maybe<T>::operator bool () const
		{
			return set;
		}

		template<class T>
		RECX14 T& Maybe<T>::operator*()
		{
			return value;
		}

		template<class T>
		RECX T const& Maybe<T>::operator*() const
		{
			return value;
		}

		template<class T>
		RECX T const& Maybe<T>::operator() (T const& default_val) const
		{
			return set ? value : default_val;
		}
	}
}