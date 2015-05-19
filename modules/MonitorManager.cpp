#include "MonitorManager.hpp"

namespace re
{
	namespace modules
	{
		MonitorManager::MonitorManager() : monitors()
		{
			int count = 0;
			GLFWmonitor ** mon = glfwGetMonitors(&count);

			monitors.reserve(count);

			for(int i = 0; i<count; i++)
				monitors.push_back(new graphics::Monitor(mon[i]));

			glfwSetMonitorCallback(&onMonitor);
		}
		
		MonitorManager::~MonitorManager()
		{
			for(auto monitor : monitors)
			{
				delete monitor;
			}
			monitors.clear();
		}

		void MonitorManager::onMonitor(GLFWmonitor *monitor, int action)
		{
			auto &monitors = GetInst()->monitors;
			if(action == GLFW_DISCONNECTED)
			{
				for(auto it = monitors.cbegin(); it != monitors.cend(); it++)
					if((*it)->monitor == monitor)
					{
						MonitorDisconnectedEvent e = { *it };
						static_cast<Emitter<MonitorDisconnectedEvent>*>(GetInst())->emit(e);
						delete(*it);
						monitors.erase(it);
						return;
					}
			}
			else
			{
				auto * mon = new graphics::Monitor(monitor);
				MonitorConnectedEvent e = { mon };
				((Emitter<MonitorConnectedEvent>*)GetInst())->emit(e);
				
				monitors.push_back(mon);
			}
		}
		
		const std::vector<graphics::Monitor*> &MonitorManager::getMonitors()
		{
			return monitors;
		}
		

		graphics::Monitor* MonitorManager::findMonitor(GLFWmonitor *monitor)
		{
			for(auto *mon: monitors)
				if(mon->monitor == monitor)
					return mon;
			return nullptr;
		}
	}
}