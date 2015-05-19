#include "Window.hpp"
#include <glfw\glfw3.h>
#include "..\modules\WindowManager.hpp"

#include <iostream>
using namespace std;

namespace re
{
	namespace graphics
	{
		Window::Window(int x, int y, int w, int h, const string &title, bool visible)
			:	x(x), y(y), w(w), h(h), title(title),
				was_windowed(true), visible(visible), wnd(nullptr),
				monitor(nullptr)
		{
			wnd = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
			glfwSetWindowPos(wnd, x, y);
			onCreate();
			modules::WindowManager::GetInst()->registerWindow(this);

			if(visible)
				show();
			else
				hide();
		}

		Window::Window(def_win_pos_t, int w, int h, const string &title, bool visible)
			:	x(), y(), w(w), h(h), title(title),
				was_windowed(true), visible(visible), wnd(nullptr),
				monitor(nullptr)
		{
			wnd = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
			glfwGetWindowPos(wnd, &x, &y);
			onCreate();
			modules::WindowManager::GetInst()->registerWindow(this);

			if(visible)
				show();
			else
				hide();
		}

		Window::Window(Monitor &monitor, const string &title, bool visible)
			:x(0), y(0), w(), h(), title(title),
			was_windowed(false), visible(visible), wnd(nullptr),
			monitor(&monitor)
		{
			VideoMode mode;
			monitor.getCurrentVideoMode(&mode);

			w = mode.width;
			h = mode.height;
			
			wnd = glfwCreateWindow(mode.width, mode.height, title.c_str(), monitor.monitor, nullptr);
			onCreate();
			modules::WindowManager::GetInst()->registerWindow(this);

			if(visible)
				show();
			else
				hide();
		}

		Window::~Window()
		{
			onClose();
			if(wnd)
				glfwDestroyWindow(wnd);
			modules::WindowManager::GetInst()->unregisterWindow(this);
		}

		bool Window::shouldClose() const
		{
			return glfwWindowShouldClose(wnd) != 0;
		}
		
		bool Window::isFullscreen() const
		{
			return monitor!=nullptr;
		}

		void Window::getFramebufferSize(int *width, int *height) const
		{
			glfwGetFramebufferSize(wnd, width, height);
		}

		int Window::getWidth() const
		{
			if(monitor)
			{
				VideoMode m;
				monitor->getCurrentVideoMode(&m);
				return m.width;
			}
			return w;
		}
		int Window::getHeight() const
		{
			if(monitor)
			{
				VideoMode m;
				monitor->getCurrentVideoMode(&m);
				return m.height;
			}
			return h;
		}

		void Window::show()
		{
			glfwShowWindow(wnd);
			visible = true;
			onVisibilityChanged(true);
		}
		void Window::hide()
		{
			glfwHideWindow(wnd);
			visible = false;
			onVisibilityChanged(false);
		}

		void Window::setTitle(const string &title)
		{
			this->title = title;
			glfwSetWindowTitle(wnd, title.c_str());
		}

		const char* Window::getTitle() const
		{
			return title.c_str();
		}
		bool Window::isVisible() const
		{
			return visible;
		}

		void Window::makeContextCurrent()
		{
			glfwMakeContextCurrent(wnd);
		}

		void Window::swapBuffers()
		{
			glfwSwapBuffers(wnd);
		}

		void Window::switchToFullscreen(graphics::Monitor *monitor)
		{
			if(!wnd || !monitor)
				return;
			glfwDestroyWindow(wnd);
			modules::WindowManager::GetInst()->unregisterWindow(this);

			VideoMode mode;
			monitor->getCurrentVideoMode(&mode);

			wnd = glfwCreateWindow(mode.width, mode.height, title.c_str(), monitor->monitor, nullptr);

			modules::WindowManager::GetInst()->registerWindow(this);
			this->monitor = monitor;
		}

		void Window::switchToWindowed(int width, int height)
		{
			if(!monitor)
			{
				if(w == width && h == height)
					return;
				w = width;
				h = height;
				glfwSetWindowSize(wnd, width, height);
				return;
			}

			glfwDestroyWindow(wnd);
			modules::WindowManager::GetInst()->unregisterWindow(this);
			
			wnd = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
			w = width;
			h = height;
			if(!was_windowed)
				glfwGetWindowPos(wnd, &x, &y);
			else
				glfwSetWindowPos(wnd, x, y);

			modules::WindowManager::GetInst()->registerWindow(this);
			this->monitor = nullptr;

			was_windowed = true;
		}

		bool Window::wasWindowed() const
		{
			return was_windowed;
		}
		
		int Window::getInternalWidth() const
		{
			return w;
		}
		
		int Window::getInternalHeight() const
		{
			return h;
		}

		void Window::onCharacter(uint codepoint) { }
		void Window::onCursorEnter(bool entered) { }
		void Window::onCursorMove(double x, double y) { }
		void Window::onKey(int key, int scancode, input::KeyAction action, int mods) { }
		void Window::onMouseButton(input::MouseButton button, input::KeyAction action, int mods) { }
		void Window::onFramebufferSizeChanged(int width, int height) { }
		void Window::onClose() { }
		void Window::onFocusChanged(bool focus) { }
		void Window::onIconify(bool iconified) { }
		void Window::onPositionChanged(int x, int y) { }
		void Window::onRefresh() { }
		void Window::onSizeChanged(int width, int height) { }
		void Window::onCreate() { }
		void Window::onVisibilityChanged(bool newValue) { }
		void Window::onScroll(double xoffset, double yoffset) { }
	}
}