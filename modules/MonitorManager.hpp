#ifndef __re_monitormanager_hpp_defined
#define __re_monitormanager_hpp_defined

#include "..\Singleton.hpp"
#include "..\graphics\Monitor.hpp"
#include "..\messaging\Emitter.hpp"
#include <vector>
#include <glfw\glfw3.h>

namespace re
{
	namespace modules
	{
		struct MonitorConnectedEvent
		{	graphics::Monitor *monitor;	};
		struct MonitorDisconnectedEvent
		{	graphics::Monitor *monitor;	};
		
		/*Manages the monitors that are connected to the machine.
		When monitors are connected to the machine, it will broadcast an event.
		@see @{re::Singleton}, @{re::messaging::Emmitter}*/
		class MonitorManager : public Singleton<MonitorManager>,
			public messaging::Emitter<MonitorConnectedEvent>,
			public messaging::Emitter<MonitorDisconnectedEvent>
		{	friend class Singleton<MonitorManager>;
			/*Stores the monitors that are currently connected.*/
			std::vector<graphics::Monitor*> monitors;
			
		public:
			/*Returns the monitors that are currently connected.*/
			const std::vector<graphics::Monitor*> &getMonitors();
			
		private:
			/*Initializes the manager and receives all currently connected monitors.
			This is private, for it is not to be called directly, as only one instance should exist at a time.*/
			MonitorManager();
			/*Destructs the manager.
			This is private, for it is not to be called directly.*/
			~MonitorManager();
			
			/*Finds the @{re::graphics::Monitor} that is associated with the given GLFWmonitor.*/
			graphics::Monitor* findMonitor(GLFWmonitor *monitor);
			/*The callback for glfw monitor events.
			@param[in] monitor: the @{GLFWmonitor} that is related to the event.
			@param[in] action: the glfw constant referring to the event that happened.*/
			static void onMonitor(GLFWmonitor *monitor, int action);
		};
	}
}

#endif