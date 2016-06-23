#include "Monitor.hpp"
#include "OpenGL.hpp"

namespace re
{
	namespace graphics
	{
		Monitor::Monitor(GLFWmonitor *monitor):
			monitor(monitor)
		{
		}

		char const* Monitor::name() const
		{
			return glfwGetMonitorName(monitor);
		}

		void Monitor::virtual_position(int *x, int *y) const
		{
			glfwGetMonitorPos(monitor, x, y);
		}

		void Monitor::current_video_mode(VideoMode *mode) const
		{
			auto const * vmode = glfwGetVideoMode(monitor);
			mode->width = vmode->width;
			mode->height = vmode->height;
			mode->frequency = vmode->refreshRate;
			mode->bitsR = vmode->redBits;
			mode->bitsG = vmode->greenBits;
			mode->bitsB = vmode->blueBits;
		}
	}
}