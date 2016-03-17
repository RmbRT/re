#ifndef __re_singleton_hpp_defined
#define __re_singleton_hpp_defined

#include "defines.hpp"
#include <vector>

namespace re
{

	class SingletonManager
	{

		/*The amount of singletons existing.*/
		static size_t _singletons;
		static std::vector<void (*)()> cleanup_delegates;


	public:
		static void registerSingleton(void (*cleanup_delegate)());
		static void unregisterSingleton(void (*cleanup_delegate)());

		/*The amount of singletons existing.*/
		static size_t singletons() { return _singletons; }
		/*Deletes all existing Singletons.*/
		static void deleteSingletons();

	};

	template<class T>
	/*Stores a singleton object of the given type.
	The object allocation is lazy, it will be allocated on first request.*/
	class Singleton
	{
	public:
		/*Returns the instance stored by this singleton.
		If it does not exist, a new one will be allocated, and a delete callback will be registered for the exit of the program.*/
		REINL static T* GetInst()
		{
			if(!instance)
			{
				instance = new T;
				SingletonManager::registerSingleton(&Del);
			}
			return instance;
		}
		static void Del()
		{
			if(!instance)
				return;
			delete instance;
			instance = nullptr;
			SingletonManager::unregisterSingleton(&Del);
		}
	protected:
		static T* instance;
	};

	template<class T>
	T* Singleton<T>::instance = nullptr;
}

#endif
