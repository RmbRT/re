#ifndef __re_windowmanager_hpp
#define __re_windowmanager_hpp

#include "../Singleton.hpp"
#include <vector>
#include "../Window.hpp"

namespace re
{
	namespace modules
	{
		class WindowManager : public Singleton<WindowManager>
		{ friend class Singleton<WindowManager>;
			std::vector<Window*> windows;
		public:
			WindowManager();

			void registerWindow(Window* wnd);
			void unregisterWindow(Window* wnd);

		private:
			~WindowManager();
			Window* findWindow(GLFWwindow *wnd);
			
			static void CharCallback(GLFWwindow *wnd, uint codepoint);
			static void CursorEnterCallback(GLFWwindow *wnd, int action);
			static void CursorPosCallback(GLFWwindow *wnd, double x, double y);
			static void FramebufferSizeCallback(GLFWwindow *wnd, int width, int height);
			static void KeyCallback(GLFWwindow *wnd, int key, int scancode, int action, int mods);
			static void MouseButtonCallback(GLFWwindow *wnd, int button, int action, int mods);
			static void ScrollCallback(GLFWwindow *wnd, double xoffset, double yoffset);
			static void CloseCallback(GLFWwindow *wnd);
			static void FocusCallback(GLFWwindow *wnd, int focus);
			static void IconifyCallback(GLFWwindow *wnd, int iconified);
			static void PosCallback(GLFWwindow *wnd, int xpos, int ypos);
			static void RefreshCallback(GLFWwindow *wnd);
			static void SizeCallback(GLFWwindow *wnd, int width, int height);
			
		};
	}
}

#endif