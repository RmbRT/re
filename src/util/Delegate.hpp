#ifndef __re_util_delegate_hpp_defined
#define __re_util_delegate_hpp_defined


#include <vector>
#include "../defines.hpp"
#include <type_traits>
#include "../LogFile.hpp"

namespace re
{
	namespace util
	{
		template<class T>
		class Delegate;

		template<class _Ret, class ...Args>
		class Delegate<_Ret(*)(Args...)>
		{
			typedef _Ret(*_Fn)(Args...);
			std::vector<_Fn> _fn;
		public:
			Delegate() { }
			Delegate(Delegate<_Ret(*)(Args...)> &&move) : _fn(std::move(move._fn)) { }


			std::vector<_Ret> operator()(Args&&... arguments) const
			{
				std::vector<_Ret> ret;
				ret.reserve(_fn.size());
				for(auto fn : _fn)
					ret.push_back(std::move(fn(std::forward<Args>(arguments)...)));
				return ret;
			}

			Delegate<_Fn> &operator+=(_Fn fn)
			{
				for(auto __fn : _fn)
					if(__fn == fn)
						return *this; 
				_fn.push_back(fn);
				return *this;
			}

			Delegate<_Fn> &operator-=(_Fn fn)
			{
				for(auto it = _fn.begin(); it != _fn.end(); it++)
					if(fn == *it)
					{
						_fn.erase(it);
						return *this;
					}
				RE_LOG("Attempted to delete a function that was not enlisted.");
				return *this;
			}
		};

		template<class ...Args>
		class Delegate<void(*)(Args...)>
		{
			typedef void _Ret;
			typedef _Ret(*_Fn)(Args...);
			std::vector<_Fn> _fn;
		public:
			Delegate() { }
			Delegate(Delegate<_Ret(*)(Args...)> &&move) : _fn(std::move(move._fn)) { }

			void operator()(Args&&... arguments) const
			{
				for(_Fn fn : _fn)
					fn(std::forward<Args>(arguments)...);
			}

			Delegate<_Fn> &operator+=(_Fn fn)
			{
				for(auto __fn : _fn)
					if(__fn == fn)
						return *this; 
				_fn.push_back(fn);
				return *this;
			}

			Delegate<_Fn> &operator-=(_Fn fn)
			{
				for(auto it = _fn.begin(); it != _fn.end(); it++)
					if(fn == *it)
					{
						_fn.erase(it);
						return *this;
					}
				RE_LOG("Attempted to delete a function that was not enlisted.");
				return *this;
			}
		};
	}
}

#endif