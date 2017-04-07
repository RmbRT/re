#include "Monitor.hpp"
#include "gl/OpenGL.hpp"

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

		math::ivec2_t Monitor::virtual_position() const
		{
			math::ivec2_t pos;
			glfwGetMonitorPos(monitor, &pos.x, &pos.y);
			return pos;
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