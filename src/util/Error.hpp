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
		using error_t = std::_If<std::is_enum<T>::value, T, bool>::type;

		template<class Enum>
		bool is_error_impl(Enum value);
		template<class T>
		bool is_error(

		template<class Enum>
		bool is_error_impl(Enum value)
		{
			static_assert(false, "Error handler error::is_error not implemented.");
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
			if(error_code)
				return "Success";
			else
				return "Failure";
		}

		template<class T>
		struct Result
		{
			Result(copy_arg<T> error_code, char const * file, char const * function, int line, char const * expression):
				error_code(error_code),
				file(file),
				function(function),
				line(line),
				expression(expression)
			{
			}

			error_t<T> error_code;
			char const * file;
			char const * function;
			int line;
			char const * expression;
		};

		template<class T>
		std::ostream & operator<<(std::ostream & o, Result<T> const& err)
		{
			return o << to_string<T>(err.error_code) << " in " << err.function << " (" << err.file << ", " << err.line << "): " << err.expression << '\n';
		}
	}
}

#define CHECKED(x, onfail) \
	do { \
		auto const& error_code = (x); \
		if(re::util::error::is_error(error_code)) \
		{ \
			onfail; \
		} \
	} while(0,0)

#define ERROR_LOG(X) std::cout << Result<decltype((x))>(error_code, __FILE__, __FUNCTION__, __LINE__, #x)
#define CHECKED_LOG(x, onfail) CHECKED(x, { ERROR_LOG(x); onfail; })

#define CRITICAL(x, onfail) CHECKED(X, { return onfail; })
#define CRITICAL_LOG(x, onfail) CHECKED_LOG(x, { return onfail; })

#ifdef RE_DEBUG
#define DBG_CHECKED CHECKED
#define DBG_CHECKED_LOG CHECKED_LOG
#define DBG_CRITICAL CRITICAL
#define DBG_CRITICAL_LOG CRITICAL_LOG
#else
#define DBG_CHECKED do { (x); } while(0,0)
#define DBG_CHECKED_LOG do { (x); } while(0,0)
#define DBG_CRITICAL do { (x); } while(0,0)
#define DBG_CRITICAL_LOG do { (x); } while(0,0)
#endif
#endif 