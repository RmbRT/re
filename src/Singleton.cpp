#include "Singleton.hpp"
#include "LogFile.hpp"

namespace re
{
	std::vector<void(*)()> SingletonManager::cleanup_delegates = std::vector<void(*)()>();
	void SingletonManager::registerSingleton(void (*cleanup_delegate)())
	{
		for(auto del : cleanup_delegates)
			RE_ASSERT(del != cleanup_delegate);
		cleanup_delegates.push_back(cleanup_delegate);
	}

	void SingletonManager::unregisterSingleton(void (*cleanup_delegate)())
	{
		for(auto it = cleanup_delegates.begin(); it != cleanup_delegates.end(); it++)
			if(*it == cleanup_delegate)
			{
				cleanup_delegates.erase(it);
				return;
			}
		RE_ASSERTION_FAILURE("Tried to unregister Singleton that was not registered.");
	}

	void SingletonManager::deleteSingletons()
	{
		while(!cleanup_delegates.empty())
			cleanup_delegates.back()();
	}
}