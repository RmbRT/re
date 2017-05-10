#include "Window.hpp"

#include "gl/OpenGL.hpp"
#include "gl/ShaderProgram.hpp"

#include "../LogFile.hpp"
#include "../util/Error.hpp"

namespace re
{
	namespace graphics
	{
		using namespace input;
		class WindowCallbacks
		{
			friend class Window;

			static void register_callbacks(
				Window * window)
			{
				glfwSetCharCallback(window->m_handle, &character_callback);
				glfwSetCursorEnterCallback(window->m_handle, &cursor_enter_callback);
				glfwSetCursorPosCallback(window->m_handle, &cursor_move_callback);
				glfwSetKeyCallback(window->m_handle, &key_callback);
				glfwSetMouseButtonCallback(window->m_handle, &mouse_button_callback);
				glfwSetFramebufferSizeCallback(window->m_handle, &framebuffer_size_callback);
				glfwSetWindowFocusCallback(window->m_handle, &focus_callback);
				glfwSetWindowIconifyCallback(window->m_handle, &iconify_callback);
				glfwSetWindowPosCallback(window->m_handle, &position_changed_callback);
				glfwSetWindowRefreshCallback(window->m_handle, &refresh_callback);
				glfwSetWindowSizeCallback(window->m_handle, &size_changed_callback);
				glfwSetScrollCallback(window->m_handle, &scroll_callback);
			}

			static ModifierKeys glfw_constant_to_modifier_keys(
				int glfw)
			{
				return {
					{ModifierKey::kShift, glfw & GLFW_MOD_SHIFT},
					{ModifierKey::kControl, glfw & GLFW_MOD_CONTROL},
					{ModifierKey::kAlt, glfw & GLFW_MOD_ALT},
					{ModifierKey::kSuper, glfw & GLFW_MOD_SUPER}
				};
			}

			static void character_callback(
				GLFWwindow * handle,
				uint_t codepoint)
			{
				Window * window = (Window*) glfwGetWindowUserPointer(handle);
				RE_DBG_ASSERT(window != nullptr);

				window->on_character(codepoint);
			}

			static void cursor_enter_callback(
				GLFWwindow * handle,
				int entered)
			{
				Window * window = (Window*) glfwGetWindowUserPointer(handle);
				RE_DBG_ASSERT(window != nullptr);

				window->on_cursor_enter(entered);
			}

			static void cursor_move_callback(
				GLFWwindow * handle,
				double x,
				double y)
			{
				Window * window = (Window*) glfwGetWindowUserPointer(handle);
				RE_DBG_ASSERT(window != nullptr);

				window->on_cursor_move(x,y);
			}

			static void key_callback(
				GLFWwindow * handle,
				int key,
				int scancode,
				int action,
				int mods)
			{
				Window * window = (Window*) glfwGetWindowUserPointer(handle);
				RE_DBG_ASSERT(window != nullptr);

				window->on_key(
					input::detail::glfw_constant_to_key(key),
					scancode,
					action != GLFW_RELEASE,
					glfw_constant_to_modifier_keys(mods));
			}

			static void mouse_button_callback(
				GLFWwindow * handle,
				int button,
				int action,
				int mods)
			{
				Window * window = (Window*) glfwGetWindowUserPointer(handle);
				RE_DBG_ASSERT(window != nullptr);

				window->on_mouse_button(
					input::detail::glfw_constant_to_mouse(button),
					action != GLFW_RELEASE,
					glfw_constant_to_modifier_keys(mods));
			}

			static void framebuffer_size_callback(
				GLFWwindow * handle,
				int width,
				int height)
			{
				Window * window = (Window*) glfwGetWindowUserPointer(handle);
				RE_DBG_ASSERT(window != nullptr);

				window->on_framebuffer_size_changed(width, height);
			}

			static void focus_callback(
				GLFWwindow * handle,
				int focused)
			{
				Window * window = (Window*) glfwGetWindowUserPointer(handle);
				RE_DBG_ASSERT(window != nullptr);

				window->on_focus_changed(focused);
			}

			static void iconify_callback(
				GLFWwindow * handle,
				int iconified)
			{
				Window * window = (Window*) glfwGetWindowUserPointer(handle);
				RE_DBG_ASSERT(window != nullptr);

				window->on_iconify(iconified);
			}

			static void position_changed_callback(
				GLFWwindow * handle,
				int x,
				int y)
			{
				Window * window = (Window*) glfwGetWindowUserPointer(handle);
				RE_DBG_ASSERT(window != nullptr);

				window->on_position_changed(x, y);
			}

			static void refresh_callback(
				GLFWwindow * handle)
			{
				Window * window = (Window*) glfwGetWindowUserPointer(handle);
				RE_DBG_ASSERT(window != nullptr);

				window->on_refresh();
			}

			static void size_changed_callback(
				GLFWwindow * handle,
				int width,
				int height)
			{
				Window * window = (Window*) glfwGetWindowUserPointer(handle);
				RE_DBG_ASSERT(window != nullptr);

				window->on_size_changed(width, height);
			}

			static void visibility_changed_callback(
				GLFWwindow * handle,
				int shown)
			{
				Window * window = (Window*) glfwGetWindowUserPointer(handle);
				RE_DBG_ASSERT(window != nullptr);

				window->on_visibility_changed(shown);
			}

			static void scroll_callback(
				GLFWwindow * handle,
				double xoffset,
				double yoffset)
			{
				Window * window = (Window*) glfwGetWindowUserPointer(handle);
				RE_DBG_ASSERT(window != nullptr);

				window->on_scroll(xoffset, yoffset);
			}
		};

		Window::Window():
			m_context(nullptr),
			m_handle(nullptr),
			m_monitor(nullptr)
		{
		}

		Window::Window(Window && move):
			m_context(move.m_context),
			m_handle(move.m_handle),
			m_monitor(move.m_monitor),

			m_title(std::move(move.m_title)),
			m_screen_bounds(move.m_screen_bounds),
			m_pixels(move.m_pixels),
			m_visible(move.m_visible),
			m_focused(move.m_focused),
			m_iconified(move.m_iconified),
			m_cursor(move.m_cursor)
		{
			move.m_context = nullptr;
			move.m_handle = nullptr;
		}

		Window &Window::operator=(Window && move)
		{
			RE_DBG_ASSERT(&move != this);

			if(exists())
				destroy();

			m_context = move.m_context;
			m_handle = move.m_handle;
			m_monitor = move.m_monitor;

			m_title = std::move(move.m_title);
			m_screen_bounds = move.m_screen_bounds;
			m_pixels = move.m_pixels;
			m_visible = move.m_visible;
			m_focused = move.m_focused;
			m_iconified = move.m_iconified;
			m_cursor = move.m_cursor;

			move.m_context = nullptr;
			move.m_handle = nullptr;
		}

		Window::~Window()
		{
			if(exists())
				destroy();
		}

		void Window::request_close()
		{
			RE_DBG_ASSERT(exists() &&
				"Tried requesting a nonexisting Window to close.");

			if(on_close_request())
				destroy();
		}

		void send_window_hints(WindowHints const& hints)
		{
			glfwWindowHint(GLFW_RESIZABLE, hints.resizable ? GL_TRUE : GL_FALSE);
			glfwWindowHint(GLFW_VISIBLE, hints.visible ? GL_TRUE : GL_FALSE);
			glfwWindowHint(GLFW_DECORATED, hints.decorated ? GL_TRUE : GL_FALSE);
			glfwWindowHint(GLFW_FOCUSED, hints.focused ? GL_TRUE : GL_FALSE);
			glfwWindowHint(GLFW_AUTO_ICONIFY, hints.auto_iconify ? GL_TRUE : GL_FALSE);
			glfwWindowHint(GLFW_FLOATING, hints.floating ? GL_TRUE : GL_FALSE);
			glfwWindowHint(GLFW_REFRESH_RATE, hints.refresh_rate(GLFW_DONT_CARE));
		}

		void send_framebuffer_hints(FramebufferHints const& hints)
		{

			glfwWindowHint(GLFW_RED_BITS, hints.red_bits(GLFW_DONT_CARE));
			glfwWindowHint(GLFW_GREEN_BITS, hints.green_bits(GLFW_DONT_CARE));
			glfwWindowHint(GLFW_BLUE_BITS, hints.blue_bits(GLFW_DONT_CARE));
			glfwWindowHint(GLFW_ALPHA_BITS, hints.alpha_bits(GLFW_DONT_CARE));

			glfwWindowHint(GLFW_DEPTH_BITS, hints.depth_bits(GLFW_DONT_CARE));
			glfwWindowHint(GLFW_STENCIL_BITS, hints.stencil_bits(GLFW_DONT_CARE));

			glfwWindowHint(GLFW_SAMPLES, hints.samples(GLFW_DONT_CARE));

			glfwWindowHint(GLFW_STEREO, hints.stereo ? GL_TRUE : GL_FALSE);
			glfwWindowHint(GLFW_SRGB_CAPABLE, hints.srgb_capable ? GL_TRUE : GL_FALSE);
			glfwWindowHint(GLFW_DOUBLEBUFFER, hints.doublebuffer ? GL_TRUE : GL_FALSE);
		}

		void send_context_hints(
			gl::ContextHints const& hints)
		{
			int client_api;
			switch(*hints.client_api)
			{
			case gl::ClientAPI::OpenGL: client_api = GLFW_OPENGL_API; break;
			case gl::ClientAPI::OpenGLES: client_api = GLFW_OPENGL_ES_API; break;
			default:
				{
					RE_DBG_ASSERT(!"Invalid Client Api value.");
				} break;
			}

			glfwWindowHint(GLFW_CLIENT_API, client_api);

			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, hints.version.valid() ? 1 : hints.version.minor());
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, hints.version.valid() ? 0 : hints.version.minor());

			int profile = GLFW_OPENGL_ANY_PROFILE;
			switch(hints.profile)
			{
			case gl::OpenGLProfile::Core: profile = GLFW_OPENGL_CORE_PROFILE; break;
			case gl::OpenGLProfile::Compat: profile = GLFW_OPENGL_COMPAT_PROFILE; break;
			case gl::OpenGLProfile::Any: profile = GLFW_OPENGL_ANY_PROFILE; break;
			default:
				RE_DBG_ASSERT(!"Invalid opengl profile enum.");
			}

			glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
		}


		bool Window::create(
			string8_t title,
			WindowHints const& window,
			FramebufferHints const& framebuffer,
			gl::ContextHints const& context)
		{
			RE_DBG_ASSERT(!exists() &&
				"Tried to create existing window.");

			send_window_hints(window);
			send_framebuffer_hints(framebuffer);
			send_context_hints(context);

			RE_CRITICAL_DBG_LOG(
				m_handle = glfwCreateWindow(
					window.width,
					window.height,
					(char const*) (unsigned char const*) title.content(),
					window.monitor ? window.monitor->monitor : nullptr,
					nullptr),
				"Window creation", false);

			glfwSetWindowUserPointer(m_handle, this);

			WindowCallbacks::register_callbacks(this);

			RE_CRITICAL_DBG_LOG(m_handle != nullptr, "Window creation", false);

			glfwMakeContextCurrent(m_handle);

			char const * version_string = nullptr;
			RE_OGL(version_string = reinterpret_cast<char const*>(glGetString(GL_VERSION)));

			RE_CRITICAL_DBG_LOG(version_string != nullptr,
				"Retrieve context version string", false);

			int major, minor;
			RE_CRITICAL_DBG_LOG(2 == sscanf(version_string, "%i.%i", &major, &minor),
				"Parsing context version string", false);

			RE_CRITICAL_DBG_LOG(m_context = create_context(context, gl::Version(major,minor)),
				"Context creation",
				false);

			reference(*m_context);

			m_window_hints = window;
			m_framebuffer_hints = framebuffer;
			m_title = std::move(title);

			glfwGetWindowPos(m_handle, &m_screen_bounds.x, &m_screen_bounds.y);
			glfwGetWindowSize(m_handle, &m_screen_bounds.w, &m_screen_bounds.h);
			glfwGetFramebufferSize(m_handle, &m_pixels.x, &m_pixels.y);

			m_visible = glfwGetWindowAttrib(m_handle, GLFW_VISIBLE);
			m_focused = glfwGetWindowAttrib(m_handle, GLFW_FOCUSED);
			m_iconified = glfwGetWindowAttrib(m_handle, GLFW_ICONIFIED);

			glfwGetCursorPos(m_handle, &m_cursor.x, &m_cursor.y);

			return true;
		}

		bool Window::create(
			string8_t title,
			WindowHints const& window,
			FramebufferHints const& framebuffer,
			Window const& share_context)
		{
			RE_DBG_ASSERT(!exists() &&
				"Tried to create existing window.");

			RE_DBG_ASSERT(share_context.exists() &&
				"Tried to share context with nonexisting window.");

			send_window_hints(window);
			send_framebuffer_hints(framebuffer);
			send_context_hints(share_context.m_context->hints());


			RE_CRITICAL_DBG_LOG(
				m_handle = glfwCreateWindow(
					window.width,
					window.height,
					(char const*) &*title.content(),
					window.monitor ? window.monitor->monitor : nullptr,
					share_context.m_handle),
				"Window creation", false);

			glfwSetWindowUserPointer(m_handle, this);

			WindowCallbacks::register_callbacks(this);

			m_window_hints = window;
			m_framebuffer_hints = framebuffer;
			m_title = std::move(title);

			glfwGetWindowPos(m_handle, &m_screen_bounds.x, &m_screen_bounds.y);
			glfwGetWindowSize(m_handle, &m_screen_bounds.w, &m_screen_bounds.h);
			glfwGetFramebufferSize(m_handle, &m_pixels.x, &m_pixels.y);

			m_visible = glfwGetWindowAttrib(m_handle, GLFW_VISIBLE);
			m_focused = glfwGetWindowAttrib(m_handle, GLFW_FOCUSED);
			m_iconified = glfwGetWindowAttrib(m_handle, GLFW_ICONIFIED);

			glfwGetCursorPos(m_handle, &m_cursor.x, &m_cursor.y);

			glfwMakeContextCurrent(m_handle);

			m_context = share_context.m_context;
			reference(*m_context);

			return true;
		}

		bool Window::recreate(
			string8_t title,
			WindowHints const& window,
			FramebufferHints const& framebuffer)
		{
			RE_DBG_ASSERT(exists() &&
				"Tried to recreate nonexisting window.");

			send_window_hints(window);
			send_framebuffer_hints(framebuffer);
			send_context_hints(m_context->hints());

			GLFWwindow * new_window;

			RE_CRITICAL_DBG_LOG(
				new_window = glfwCreateWindow(
					window.width,
					window.height,
					(char const*) &*title.content(),
					window.monitor ? window.monitor->monitor : nullptr,
					m_handle),
				"Window recreation", false);

			glfwSetWindowUserPointer(m_handle, this);

			WindowCallbacks::register_callbacks(this);

			gl::Context * const shared_context = m_context;
			// add one reference, because destroy() removes one.
			reference(*shared_context);
			destroy();

			m_handle = new_window;
			m_context = shared_context;

			m_window_hints = window;
			m_framebuffer_hints = framebuffer;
			m_title = std::move(title);

			glfwGetWindowPos(m_handle, &m_screen_bounds.x, &m_screen_bounds.y);
			glfwGetWindowSize(m_handle, &m_screen_bounds.w, &m_screen_bounds.h);
			glfwGetFramebufferSize(m_handle, &m_pixels.x, &m_pixels.y);

			m_visible = glfwGetWindowAttrib(m_handle, GLFW_VISIBLE);
			m_focused = glfwGetWindowAttrib(m_handle, GLFW_FOCUSED);
			m_iconified = glfwGetWindowAttrib(m_handle, GLFW_ICONIFIED);

			glfwGetCursorPos(m_handle, &m_cursor.x, &m_cursor.y);

			return true;
		}

		void Window::destroy()
		{
			RE_DBG_ASSERT(exists() &&
				"Tried to destroy nonexisting window.");

			dereference(*m_context);

			if(!m_context->references())
				delete m_context;

			glfwDestroyWindow(m_handle);


			m_handle = nullptr;
			m_context = nullptr;
		}

		void Window::show()
		{
			RE_DBG_ASSERT(exists());

			if(!m_visible)
			{
				m_visible = true;
				glfwShowWindow(m_handle);
				on_visibility_changed(true);
			}
		}

		void Window::hide()
		{
			RE_DBG_ASSERT(exists());

			if(m_visible)
			{
				m_visible = false;
				glfwHideWindow(m_handle);
				on_visibility_changed(false);
			}
		}

		void Window::set_cursor(math::double2_t const& pos)
		{
			RE_DBG_ASSERT(exists() &&
				"Tried to access nonexisting window.");
			glfwSetCursorPos(m_handle, pos.x, pos.y);
			m_cursor = pos;
		}

		void Window::set_position(int x, int y)
		{
			RE_DBG_ASSERT(exists() &&
				"Tried to access nonexisting window.");
			glfwSetWindowPos(m_handle, x, y);
			m_screen_bounds.x = x;
			m_screen_bounds.y = y;
		}

		void Window::set_size(int w, int h)
		{
			RE_DBG_ASSERT(exists() &&
				"Tried to access nonexisting window.");
			glfwSetWindowSize(m_handle, w, h);
			m_screen_bounds.w = w;
			m_screen_bounds.h = h;
		}

		void Window::set_title(string8_t title)
		{
			RE_DBG_ASSERT(exists() &&
				"Tried to access nonexisting window.");

			glfwSetWindowTitle(m_handle, (char const*) &*title.content());
			m_title = std::move(title);
		}

		void Window::make_context_current()
		{
			RE_DBG_ASSERT(exists() &&
				"Tried to access nonexisting window.");

			if(!m_context->current())
				glfwMakeContextCurrent(m_handle), make_current(*m_context);
		}

		void Window::swap_buffers()
		{
			RE_DBG_ASSERT(exists() &&
				"Tried to access nonexisting window.");

			glfwSwapBuffers(m_handle);
		}

		void Window::poll_events()
		{
			glfwPollEvents();
		}

		void Window::wait_events()
		{
			glfwWaitEvents();
		}
	}
}