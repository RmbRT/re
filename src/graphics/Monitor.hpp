#ifndef __re_monitor_hpp_defined
#define __re_monitor_hpp_defined

#include "..\types.hpp"
#define GLFW_INCLUDE_NONE
#include <glfw\glfw3.h>
#include "..\math\Vector.hpp"
#include "VideoMode.hpp"

namespace re
{
	class Window;
	namespace graphics
	{
		/** Represents a monitor attached to the machine. */
		class Monitor
		{
			friend class re::Window;
			/** The glfw monitor that represents the attached monitor. */
			GLFWmonitor *monitor;
			
			/** Constructs a monitor object. */
			Monitor(GLFWmonitor *monitor);
		public:
			/** The device name of the monitor.
			@return
				The name of the device.
				! Do not delete / free the memory, it is handled by GLFW. */
			char const* name() const;
			void virtual_position(int *x, int *y) const;
			void current_video_mode(VideoMode * mode) const;
		};
		
	}
}

#endif