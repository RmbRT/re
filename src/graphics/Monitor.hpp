#ifndef __re_monitor_hpp_defined
#define __re_monitor_hpp_defined

#include "../types.hpp"
#define GLFW_INCLUDE_NONE
#include "gl/OpenGL.hpp"
#include "../math/Vector.hpp"
#include "VideoMode.hpp"

namespace re
{
	namespace graphics
	{
		class Window;
		/** Represents a monitor attached to the machine. */
		class Monitor
		{
			friend class re::graphics::Window;
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
			math::ivec2_t virtual_position() const;
			void current_video_mode(VideoMode * mode) const;
		};
	}
}

#endif