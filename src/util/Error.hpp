#ifndef __error_error_hpp_defined
#define __error_error_hpp_defined

#include <string>
#include <type_traits>
#include <iostream>
#include <cstdlib>

#include "Argument.hpp"

namespace re
{
	namespace util
	{
		template<class T>
		using error_t = typename std::conditional<std::is_enum<T>::value,
			T,
			typename std::conditional<std::is_same<T, char const*>::value,
				char const*,
				bool>::type>::type;

		template<class Enum>
		bool is_error_impl(Enum value);

		template<>
		bool is_error_impl<bool>(bool value)
		{
			return !value;
		}

		template<class T>
		bool is_error(copy_arg_t<T> value)
		{
			return is_error_impl<error_t<T>>(value);
		}

		template<class Enum>
		char const * to_string_impl(Enum error);

		template<class T>
		char const * to_string(copy_arg_t<T> error)
		{
			return to_string_impl<error_t<T>>(error);
		}

		template<>
		char const * to_string_impl<bool>(bool error_code)
		{
			return error_code ? "Success":"Failure";
		}

		template<>
		char const * to_string_impl<char const*>(char const * error_msg)
		{
			return error_msg ? error_msg:"(null)";
		}
	}
}

#define RE_CHECKED(x, onfail) \
	do { \
		copy_arg_t<decltype((x))> error_code = (x); \
		if(::re::util::is_error(error_code)) \
		{ \
			onfail; \
		} \
	} while(0,0)

#define RE_ERROR_LOG(name) void(std::clog << __FILE__ << '@' << __LINE__ << " in " << __FUNCTION__ << ":\n\t" << name << ": " << re::util::to_string((error_code)) << '\n')
#define RE_CHECKED_LOG(x, name, onfail) RE_CHECKED(x, { RE_ERROR_LOG(name); onfail; })

#define RE_CRITICAL(x, errcode) RE_CHECKED(x, { return errcode; })
#define RE_CRITICAL_LOG(x, name, errcode) RE_CHECKED_LOG(x, name, { return errcode; })

#define RE_FATAL(x) RE_CHECKED(x, { RE_SWITCH(std::abort(),std::exit(EXIT_FAILURE)); })
#define RE_FATAL_LOG(x, name) RE_CHECKED_LOG(x, name, { RE_SWITCH(std::abort(),std::exit(EXIT_FAILURE)); })

#ifdef RE_DEBUG
	#define RE_CHECKED_DBG_LOG RE_CHECKED_LOG
	#define RE_CRITICAL_DBG_LOG RE_CRITICAL_LOG
	#define RE_FATAL_DBG_LOG RE_FATAL_LOG
#else
	#define RE_CHECKED_DBG_LOG(x, name, errcode) RE_CHECKED(x, errcode)
	#define RE_CRITICAL_DBG_LOG(x, name, errcode) RE_CRITICAL(x, errcode)
	#define RE_FATAL_DBG_LOG(x, name) RE_FATAL(x)
#endif


#endif 