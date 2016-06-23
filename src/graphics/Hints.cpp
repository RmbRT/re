#include "Hints.hpp"

namespace re
{
	namespace graphics
	{
		WindowHints::WindowHints(Monitor const& monitor, string title):
			resizable(false),
			visible(true),
			decorated(false),
			focused(true),
			auto_iconify(true),
			floating(false),
			monitor(&monitor)
		{
			VideoMode vm;
			monitor.current_video_mode(vm);

			width = vm.width;
			height = vm.height;
		}

		WindowHints::WindowHints(int width, int height, string title):
			resizable(true),
			visible(true),
			decorated(true),
			focused(true),
			auto_iconify(false),
			floating(false),
			monitor(nullptr),
			width(width),
			height(height)
		{
		}


		FramebufferHints::FramebufferHints():
			stereo(false),
			srgb_capable(false),
			doublebuffer(true)
		{
		}

		FramebufferHints::FramebufferHints(int samples, bool doublebuffer, bool srgb_capable):
			stereo(false),
			srgb_capable(srgb_capable),
			doublebuffer(doublebuffer),
			samples(samples)
		{
		}

		ContextHints::ContextHints():
			version(0,0),
			profile(OpenGLProfile::Any)
		{
		}
	}
}