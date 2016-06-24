#ifndef __re_util_argument_hpp_defined
#define __re_util_argument_hpp_defined

#include <type_traits>


namespace re
{
	namespace util
	{
		template<class T>
		using copy_t = T const&;
		template<class T>
		using move_t = typename std::remove_const<T>::type &&;

#if defined(__GNUC__) && (__GNUC__ < 5)
		// g++ 4.8 does not properly support the type checks, so we have to assume the worst case.
		template<class T>
		using copy_arg_t = copy_t<T>;

		template<class T>
		using move_arg_t = move_t<T>;
#else
		template<class T>
		using copy_arg_t = typename std::conditional<
			sizeof(T) <= sizeof(void*)
			&& std::is_trivially_copy_constructible<T>::value
			&& std::is_trivially_move_constructible<T>::value,
			T,
			copy_t<T>>
				::type;

		template<class T>
		using move_arg_t = std::conditional<
			sizeof(T) <= sizeof(void*)
			&& std::is_trivially_copy_constructible<T>::value
			&& std::is_trivially_move_constructible<T>::value,
			T,
			move_t<T>>
				::type;
#endif

		
	}
}

#endif
