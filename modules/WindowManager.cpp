#include "WindowManager.hpp"

#define GL_TRUE 1
#define GL_FALSE 0


namespace re
{
	namespace modules
	{

		input::Key glfwMbToEnum(int glfw)
		{
			switch(glfw)
			{
			case GLFW_MOUSE_BUTTON_1: {return input::Key::MB_1; } break;
			case GLFW_MOUSE_BUTTON_2: {return input::Key::MB_2; } break;
			case GLFW_MOUSE_BUTTON_3: {return input::Key::MB_3; } break;
			case GLFW_MOUSE_BUTTON_4: {return input::Key::MB_4; } break;
			case GLFW_MOUSE_BUTTON_5: {return input::Key::MB_5; } break;
			case GLFW_MOUSE_BUTTON_6: {return input::Key::MB_6; } break;
			case GLFW_MOUSE_BUTTON_7: {return input::Key::MB_7; } break;
			case GLFW_MOUSE_BUTTON_8: {return input::Key::MB_8; } break;
			default:
				{
					string num = std::to_string(glfw);
					num+=" is not a valid Mouse Button.";
					RE_ASSERTION_FAILURE(num.c_str());
				} break;
			}
		}

		input::Key glfwJoyToEnum(int glfw)
		{
			switch(glfw)
			{
			case GLFW_JOYSTICK_1: {return input::Key::JOY_1; } break;
			case GLFW_JOYSTICK_2: {return input::Key::JOY_2; } break;
			case GLFW_JOYSTICK_3: {return input::Key::JOY_3; } break;
			case GLFW_JOYSTICK_4: {return input::Key::JOY_4; } break;
			case GLFW_JOYSTICK_5: {return input::Key::JOY_5; } break;
			case GLFW_JOYSTICK_6: {return input::Key::JOY_6; } break;
			case GLFW_JOYSTICK_7: {return input::Key::JOY_7; } break;
			case GLFW_JOYSTICK_8: {return input::Key::JOY_8; } break;
			case GLFW_JOYSTICK_9: {return input::Key::JOY_9; } break;
			case GLFW_JOYSTICK_10: {return input::Key::JOY_10; } break;
			case GLFW_JOYSTICK_11: {return input::Key::JOY_11; } break;
			case GLFW_JOYSTICK_12: {return input::Key::JOY_12; } break;
			case GLFW_JOYSTICK_13: {return input::Key::JOY_13; } break;
			case GLFW_JOYSTICK_14: {return input::Key::JOY_14; } break;
			case GLFW_JOYSTICK_15: {return input::Key::JOY_15; } break;
			case GLFW_JOYSTICK_16: {return input::Key::JOY_16; } break;
			default:
				{
					string num = std::to_string(glfw);
					num+=" is not a valid Joystick button.";
					RE_ASSERTION_FAILURE(num.c_str());
				} break;
			}
		}

		input::Key glfwKeyToEnum(int glfw)
		{
			switch(glfw)
			{
			case GLFW_KEY_F1: {return input::Key::K_F1; } break;
			case GLFW_KEY_F2: {return input::Key::K_F2; } break;
			case GLFW_KEY_F3: {return input::Key::K_F3; } break;
			case GLFW_KEY_F4: {return input::Key::K_F4; } break;
			case GLFW_KEY_F5: {return input::Key::K_F5; } break;
			case GLFW_KEY_F6: {return input::Key::K_F6; } break;
			case GLFW_KEY_F7: {return input::Key::K_F7; } break;
			case GLFW_KEY_F8: {return input::Key::K_F8; } break;
			case GLFW_KEY_F9: {return input::Key::K_F9; } break;
			case GLFW_KEY_F10: {return input::Key::K_F10; } break;
			case GLFW_KEY_F11: {return input::Key::K_F11; } break;
			case GLFW_KEY_F12: {return input::Key::K_F12; } break;
			case GLFW_KEY_F13: {return input::Key::K_F13; } break;
			case GLFW_KEY_F14: {return input::Key::K_F14; } break;
			case GLFW_KEY_F15: {return input::Key::K_F15; } break;
			case GLFW_KEY_F16: {return input::Key::K_F16; } break;
			case GLFW_KEY_F17: {return input::Key::K_F17; } break;
			case GLFW_KEY_F18: {return input::Key::K_F18; } break;
			case GLFW_KEY_F19: {return input::Key::K_F19; } break;
			case GLFW_KEY_F20: {return input::Key::K_F20; } break;
			case GLFW_KEY_F21: {return input::Key::K_F21; } break;
			case GLFW_KEY_F22: {return input::Key::K_F22; } break;
			case GLFW_KEY_F23: {return input::Key::K_F23; } break;
			case GLFW_KEY_F24: {return input::Key::K_F24; } break;
			case GLFW_KEY_F25: {return input::Key::K_F25; } break;
			case GLFW_KEY_SPACE: {return input::Key::K_SPACE; } break;
			case GLFW_KEY_APOSTROPHE: {return input::Key::K_APOSTROPHE; } break;
			case GLFW_KEY_COMMA: {return input::Key::K_COMMA; } break;
			case GLFW_KEY_MINUS: {return input::Key::K_MINUS; } break;
			case GLFW_KEY_PERIOD: {return input::Key::K_PERIOD; } break;
			case GLFW_KEY_SLASH: {return input::Key::K_SLASH; } break;
			case GLFW_KEY_SEMICOLON: {return input::Key::K_SEMICOLON; } break;
			case GLFW_KEY_EQUAL: {return input::Key::K_EQUAL; } break;
			case GLFW_KEY_LEFT_BRACKET: {return input::Key::K_LEFT_BRACKET; } break;
			case GLFW_KEY_BACKSLASH: {return input::Key::K_BACKSLASH; } break;
			case GLFW_KEY_RIGHT_BRACKET: {return input::Key::K_RIGHT_BRACKET; } break;
			case GLFW_KEY_GRAVE_ACCENT: {return input::Key::K_GRAVE_ACCENT; } break;
			case GLFW_KEY_WORLD_1: {return input::Key::K_WORLD_1; } break;
			case GLFW_KEY_WORLD_2: {return input::Key::K_WORLD_2; } break;
			case GLFW_KEY_ESCAPE: {return input::Key::K_ESCAPE; } break;
			case GLFW_KEY_ENTER: {return input::Key::K_ENTER; } break;
			case GLFW_KEY_TAB: {return input::Key::K_TAB; } break;
			case GLFW_KEY_BACKSPACE: {return input::Key::K_BACKSPACE; } break;
			case GLFW_KEY_INSERT: {return input::Key::K_INSERT; } break;
			case GLFW_KEY_DELETE: {return input::Key::K_DELETE; } break;
			case GLFW_KEY_PRINT_SCREEN: {return input::Key::K_PRINT_SCREEN; } break;
			case GLFW_KEY_PAUSE: {return input::Key::K_PAUSE; } break;
			case GLFW_KEY_MENU: {return input::Key::K_MENU; } break;
			case GLFW_KEY_0: {return input::Key::K_0; } break;
			case GLFW_KEY_1: {return input::Key::K_1; } break;
			case GLFW_KEY_2: {return input::Key::K_2; } break;
			case GLFW_KEY_3: {return input::Key::K_3; } break;
			case GLFW_KEY_4: {return input::Key::K_4; } break;
			case GLFW_KEY_5: {return input::Key::K_5; } break;
			case GLFW_KEY_6: {return input::Key::K_6; } break;
			case GLFW_KEY_7: {return input::Key::K_7; } break;
			case GLFW_KEY_8: {return input::Key::K_8; } break;
			case GLFW_KEY_9: {return input::Key::K_9; } break;
			case GLFW_KEY_RIGHT: {return input::Key::K_RIGHT; } break;
			case GLFW_KEY_LEFT: {return input::Key::K_LEFT; } break;
			case GLFW_KEY_DOWN: {return input::Key::K_DOWN; } break;
			case GLFW_KEY_UP: {return input::Key::K_UP; } break;
			case GLFW_KEY_CAPS_LOCK: {return input::Key::K_CAPS_LOCK; } break;
			case GLFW_KEY_SCROLL_LOCK: {return input::Key::K_SCROLL_LOCK; } break;
			case GLFW_KEY_NUM_LOCK: {return input::Key::K_NUM_LOCK; } break;
			case GLFW_KEY_A: {return input::Key::K_A; } break;
			case GLFW_KEY_B: {return input::Key::K_B; } break;
			case GLFW_KEY_C: {return input::Key::K_C; } break;
			case GLFW_KEY_D: {return input::Key::K_D; } break;
			case GLFW_KEY_E: {return input::Key::K_E; } break;
			case GLFW_KEY_F: {return input::Key::K_F; } break;
			case GLFW_KEY_G: {return input::Key::K_G; } break;
			case GLFW_KEY_H: {return input::Key::K_H; } break;
			case GLFW_KEY_I: {return input::Key::K_I; } break;
			case GLFW_KEY_J: {return input::Key::K_J; } break;
			case GLFW_KEY_K: {return input::Key::K_K; } break;
			case GLFW_KEY_L: {return input::Key::K_L; } break;
			case GLFW_KEY_M: {return input::Key::K_M; } break;
			case GLFW_KEY_N: {return input::Key::K_N; } break;
			case GLFW_KEY_O: {return input::Key::K_O; } break;
			case GLFW_KEY_P: {return input::Key::K_P; } break;
			case GLFW_KEY_Q: {return input::Key::K_Q; } break;
			case GLFW_KEY_R: {return input::Key::K_R; } break;
			case GLFW_KEY_S: {return input::Key::K_S; } break;
			case GLFW_KEY_T: {return input::Key::K_T; } break;
			case GLFW_KEY_U: {return input::Key::K_U; } break;
			case GLFW_KEY_V: {return input::Key::K_V; } break;
			case GLFW_KEY_W: {return input::Key::K_W; } break;
			case GLFW_KEY_X: {return input::Key::K_X; } break;
			case GLFW_KEY_Y: {return input::Key::K_Y; } break;
			case GLFW_KEY_Z: {return input::Key::K_Z; } break;
			case GLFW_KEY_KP_0: {return input::Key::K_KP0; } break;
			case GLFW_KEY_KP_1: {return input::Key::K_KP1; } break;
			case GLFW_KEY_KP_2: {return input::Key::K_KP2; } break;
			case GLFW_KEY_KP_3: {return input::Key::K_KP3; } break;
			case GLFW_KEY_KP_4: {return input::Key::K_KP4; } break;
			case GLFW_KEY_KP_5: {return input::Key::K_KP5; } break;
			case GLFW_KEY_KP_6: {return input::Key::K_KP6; } break;
			case GLFW_KEY_KP_7: {return input::Key::K_KP7; } break;
			case GLFW_KEY_KP_8: {return input::Key::K_KP8; } break;
			case GLFW_KEY_KP_9: {return input::Key::K_KP9; } break;
			case GLFW_KEY_PAGE_UP: {return input::Key::K_PAGE_UP; } break;
			case GLFW_KEY_PAGE_DOWN: {return input::Key::K_PAGE_DOWN; } break;
			case GLFW_KEY_HOME: {return input::Key::K_HOME; } break;
			case GLFW_KEY_END: {return input::Key::K_END; } break;
			case GLFW_KEY_LEFT_SHIFT: {return input::Key::K_LEFT_SHIFT; } break;
			case GLFW_KEY_LEFT_CONTROL: {return input::Key::K_LEFT_CONTROL; } break;
			case GLFW_KEY_LEFT_ALT: {return input::Key::K_LEFT_ALT; } break;
			case GLFW_KEY_LEFT_SUPER: {return input::Key::K_LEFT_SUPER; } break;
			case GLFW_KEY_RIGHT_SHIFT: {return input::Key::K_RIGHT_SHIFT; } break;
			case GLFW_KEY_RIGHT_CONTROL: {return input::Key::K_RIGHT_CONTROL; } break;
			case GLFW_KEY_RIGHT_ALT: {return input::Key::K_RIGHT_ALT; } break;
			case GLFW_KEY_RIGHT_SUPER: {return input::Key::K_RIGHT_SUPER; } break;
			case GLFW_KEY_KP_DECIMAL: {return input::Key::K_KP_DECIMAL; } break;
			case GLFW_KEY_KP_DIVIDE: {return input::Key::K_KP_DIVIDE; } break;
			case GLFW_KEY_KP_MULTIPLY: {return input::Key::K_KP_MULTIPLY; } break;
			case GLFW_KEY_KP_SUBTRACT: {return input::Key::K_KP_SUBTRACT; } break;
			case GLFW_KEY_KP_ADD: {return input::Key::K_KP_ADD; } break;
			case GLFW_KEY_KP_ENTER: {return input::Key::K_KP_ENTER; } break;
			case GLFW_KEY_KP_EQUAL: {return input::Key::K_KP_EQUAL; } break;
			default:
				{
					string num = std::to_string(glfw);
					num+=" is not a valid Key.";
					RE_ASSERTION_FAILURE(num.c_str());
				} break;
			}
		}

		WindowManager::WindowManager() : windows()
		{	}
		WindowManager::~WindowManager()
		{	}
		
		void WindowManager::registerWindow(Window *wnd)
		{
			windows.push_back(wnd);
			GLFWwindow *glfw = wnd->wnd;
			glfwSetCharCallback(glfw, &CharCallback);
			glfwSetCursorEnterCallback(glfw, &CursorEnterCallback);
			glfwSetCursorPosCallback(glfw, &CursorPosCallback);
			glfwSetFramebufferSizeCallback(glfw, &FramebufferSizeCallback);
			glfwSetKeyCallback(glfw, &KeyCallback);
			glfwSetMouseButtonCallback(glfw, &MouseButtonCallback);
			glfwSetScrollCallback(glfw, &ScrollCallback);
			glfwSetWindowCloseCallback(glfw, &CloseCallback);
			glfwSetWindowFocusCallback(glfw, &FocusCallback);
			glfwSetWindowIconifyCallback(glfw, &IconifyCallback);
			glfwSetWindowPosCallback(glfw, &PosCallback);
			glfwSetWindowSizeCallback(glfw, &SizeCallback);
			glfwSetWindowRefreshCallback(glfw, &RefreshCallback);
		}
		void WindowManager::unregisterWindow(Window *wnd)
		{
			for(auto it = windows.begin(); it != windows.end(); it++)
				if((*it) == wnd)
				{
					windows.erase(it);
					return;
				}
		}

		Window* WindowManager::findWindow(GLFWwindow *wnd)
		{
			for(const auto &w : windows)
			{
				if(w->wnd == wnd)
					return w;
			}
			return nullptr;
		}

		void WindowManager::CharCallback(GLFWwindow *wnd, uint codepoint)
		{
			auto window = GetInst()->findWindow(wnd);
			window->onCharacter(codepoint);
		}

		void WindowManager::CloseCallback(GLFWwindow *wnd)
		{
			auto window = GetInst()->findWindow(wnd);
			window->onClose();
		}

		void WindowManager::CursorEnterCallback(GLFWwindow *wnd, int action)
		{
			auto window = GetInst()->findWindow(wnd);
			window->onCursorEnter(action == GL_TRUE);
		}

		void WindowManager::CursorPosCallback(GLFWwindow *wnd, double xpos, double ypos)
		{
			auto window = GetInst()->findWindow(wnd);
			window->onCursorMove(xpos, ypos);
		}
		void WindowManager::FocusCallback(GLFWwindow *wnd, int action)
		{
			auto window = GetInst()->findWindow(wnd);
			window->onFocusChanged(action == GL_TRUE);
		}
		void WindowManager::FramebufferSizeCallback(GLFWwindow *wnd, int width, int height)
		{
			auto window = GetInst()->findWindow(wnd);
			window->onFramebufferSizeChanged(width, height);
		}
		void WindowManager::IconifyCallback(GLFWwindow *wnd, int iconify)
		{
			auto window = GetInst()->findWindow(wnd);
			window->onIconify(iconify == GL_TRUE);
		}
		void WindowManager::KeyCallback(GLFWwindow *wnd, int key, int scancode, int action, int mods)
		{
			auto window = GetInst()->findWindow(wnd);
			if(action == GLFW_REPEAT)
				return;

			bool pressed = action != GLFW_RELEASE;
			window->onKey(glfwKeyToEnum(key), scancode, pressed, mods);
		}
		void WindowManager::MouseButtonCallback(GLFWwindow *wnd, int button, int action, int mods)
		{
			auto window = GetInst()->findWindow(wnd);
			if(action == GLFW_REPEAT)
				return;

			bool pressed = action != GLFW_RELEASE;
			window->onMouseButton(glfwMbToEnum(button), pressed, mods);
		}

		void WindowManager::PosCallback(GLFWwindow *wnd, int xpos, int ypos)
		{
			auto window = GetInst()->findWindow(wnd);
			window->onPositionChanged(xpos, ypos);
		}

		void WindowManager::RefreshCallback(GLFWwindow *wnd)
		{
			auto window = GetInst()->findWindow(wnd);
			window->onRefresh();
		}

		void WindowManager::ScrollCallback(GLFWwindow *wnd, double xoffset, double yoffset)
		{
			auto window = GetInst()->findWindow(wnd);
			window->onScroll(xoffset, yoffset);
		}

		void WindowManager::SizeCallback(GLFWwindow *wnd, int width, int height)
		{
			auto window = GetInst()->findWindow(wnd);
			window->onSizeChanged(width, height);
		}
	}
}