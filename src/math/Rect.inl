namespace re
{
	namespace math
	{
		template<class T>
		RECX Rect<T>::Rect():
			x(),
			y(),
			w(),
			h()
		{
		}
		template<class T>
		RECX Rect<T>::Rect(
			copy_arg_t<T> x,
			copy_arg_t<T> y,
			copy_arg_t<T> w,
			copy_arg_t<T> h):
			x(x),
			y(y),
			w(w),
			h(h)
		{
		}
	}
}