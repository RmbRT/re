#ifndef __re_util_argument_hpp_defined
#define __re_util_argument_hpp_defined

#include <type_traits>

namespace re
{
	namespace util
	{
		template<class T>
		using copy_t = std::add_lvalue_reference_t<std::add_const_t<T>>;
		template<class T>
		using move_t = std::add_rvalue_reference_t<std::remove_const_t<T>>;

		template<class T>
		using copy_arg_t = std::_If<
			sizeof(T) <= sizeof(void*)
			&& std::is_trivially_copy_constructible<T>::value
			&& std::is_trivially_move_constructible<T>::value,
			T,
			copy_t<T>>
				::type;

		template<class T>
		using move_arg_t = std::_If<
			sizeof(T) <= sizeof(void*)
			&& std::is_trivially_move_constructible<T>::value
			&& std::is_trivially_copy_constructible<T>::value,
			T,
			move_t<T>>
				::type;
	}
}

#endif
