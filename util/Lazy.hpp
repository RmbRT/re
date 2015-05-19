#ifndef __re_util_lazy_hpp_defined
#define __re_util_lazy_hpp_defined

#include "../base_types.hpp"
#include "NotNull.hpp"

namespace re
{
	namespace util
	{
		template<class T>
		/*Stores an unitialized instance of a type.
		The destructor of the stored type will not be called by lazy.*/
		struct  lazy
		{
			/*raw instance.*/
			byte data[sizeof(T)];

		public:
			operator notnull<T>() { return reinterpret<T>((byte&)data[0]); }
			operator notnull<const T>() const  { return reinterpret<const T>((byte&)data[0]); }

			T* operator&() { return reinterpret_cast<T*>(data); }

			void destruct() const { reinterpret_cast<T*>(const_cast<byte*>(data))->~T(); }

			lazy() = default;
			lazy(lazy<T> &&move) { new (data) T(std::move(move.data)); }
		};
	}
}

#endif