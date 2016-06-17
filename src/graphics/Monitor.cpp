#include "Monitor.hpp"
#include "OpenGL.hpp"

namespace re
{
	namespace graphics
	{
		Monitor::Monitor(GLFWmonitor *monitor) : monitor(monitor) { }
		const char* Monitor::getName() const
		{
			return glfwGetMonitorName(monitor);
		}

		void Monitor::getVirtualPosition(int *x, int *y) const
		{
			glfwGetMonitorPos(monitor, x, y);
		}

		void Monitor::getCurrentVideoMode(VideoMode *mode) const
		{
			const auto *vmode = glfwGetVideoMode(monitor);
			mode->width = vmode->width;
			mode->height = vmode->height;
			mode->frequency = vmode->refreshRate;
			mode->bitsR = vmode->redBits;
			mode->bitsG = vmode->greenBits;
			mode->bitsB = vmode->blueBits;
		}
	}
}