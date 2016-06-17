#ifndef __error_error_hpp_defined
#define __error_error_hpp_defined

#include <string>
#include <type_traits>
#include <iostream>

#include "Argument.hpp"

namespace re
{
	namespace util
	{
		template<class T>
		using error_t = std::_If<std::is_enum<T>::value,
			T,
			std::_If<std::is_same<T, char const*>::value,
				char const*,
				bool>::type>::type;

		template<class Enum>
		bool is_error_impl(Enum value);
		template<class T>
		bool is_error(error_t<T> value);

		template<class Enum>
		bool is_error_impl(Enum value)
		{
			static_assert(false, "error::is_error not implemented.");
		}

		template<class T>
		bool is_error(copy_arg_t<T> value)
		{
			return is_error_impl<error_t<T>>(value);
		}

		template<>
		bool is_error_impl<bool>(bool value)
		{
			return !value;
		}

		template<class Enum>
		char const * to_string_impl(Enum error)
		{
			static_assert(false, "Error handler error::to_string not implemented.");
		}

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
		auto const& error_code = (x); \
		if(re::util::is_error(error_code)) \
		{ \
			onfail; \
		} \
	} while(0,0)

#define RE_ERROR_LOG(name) void(std::clog << __FILE__ << '@' << __LINE__ << " in " << __FUNCTION__ << ":\n\t" << name << ": " << re::util::to_string((error_code)) << '\n')
#define RE_CHECKED_LOG(x, name, onfail) RE_CHECKED(x, { RE_ERROR_LOG(name); onfail; })

#define RE_CRITICAL(x, errcode) RE_CHECKED(x, { return errcode; })
#define RE_CRITICAL_LOG(x, name, errcode) RE_CHECKED_LOG(x, name, { return errcode; })

#ifdef RE_DEBUG
	#define RE_CHECKED_DBG_LOG RE_CHECKED_LOG
	#define RE_CRITICAL_DBG_LOG RE_CRITICAL_LOG
#else
	#define RE_CHECKED_DBG_LOG(x, name, errcode) RE_CHECKED(x, errcode)
	#define RE_CRITICAL_DBG_LOG(x, name, errcode) RE_CRITICAL(x, errcode)
#endif


#endif 