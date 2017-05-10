#ifndef __re_util_maybe_hpp_defined
#define __re_util_maybe_hpp_defined

#include "Argument.hpp"

#include "../defines.hpp"

namespace re
{
	namespace util
	{
		template<class T>
		struct Maybe
		{
			RECX Maybe();
			RECX Maybe(copy_arg_t<T> value);

			bool set;
			T value;

			RECX operator bool () const;

			RECX14 T& operator*();
			RECX T const& operator*() const;

			RECX T const& operator() (T const& default_val) const;
		};
	}
}

#include "Maybe.inl"

#endif