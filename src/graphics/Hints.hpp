#ifndef __re_graphics_hints_hpp_defined
#define __re_graphics_hints_hpp_defined

#include "../util/Maybe.hpp"
#include "Version.hpp"
#include "VideoMode.hpp"

namespace re
{
	namespace graphics
	{


		enum class ClientAPI
		{
			OpenGL,
			OpenGLES
		};

		enum class OpenGLProfile
		{
			Core,
			Compat,
			Any
		};

		/** The window hints for window creation. */
		struct WindowHints
		{
			WindowHints(Monitor const& monitor);
			WindowHints(int width, int height);

			bool resizable;
			bool visible;
			bool decorated;
			bool focused;
			bool auto_iconify;
			bool floating;

			Monitor * monitor;
			int width, height;

			util::Maybe<int> refresh_rate;
		};

		struct FramebufferHints
		{
			FramebufferHints();
			FramebufferHints(int samples, bool doublebuffer, bool srgb_capable);

			bool stereo;
			bool srgb_capable;
			bool doublebuffer;

			util::Maybe<int>
				red_bits,
				green_bits,
				blue_bits,
				alpha_bits;

			util::Maybe<int> depth_bits;
			util::Maybe<int> stencil_bits;

			util::Maybe<int> samples;
		};

		struct ContextHints
		{
			ContextHints();
			Version version;
			util::Maybe<ClientAPI> client_api;
			OpenGLProfile profile;
		};
	}
}

#endif