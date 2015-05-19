#include "Window.hpp"
#include <glfw/glfw3.h>
#include "modules/WindowManager.hpp"
#include <gl3/glew.h>
#include "LogFile.hpp"
#include "graphics/ShaderProgram.hpp"

namespace re
{
	inline void initGlew(Window &wnd)
	{
		wnd.makeContextCurrent();
		glewExperimental = TRUE;
		GLenum err = glewInit();
		if(err != GLEW_OK)
		{
			LogFile::GetInst()->writef("Could not initialize GLEW for window %s: %s", wnd.getTitle(), glewGetErrorString(err));
		}
		while(glGetError());
		LogFile::GetInst()->writefln("Using OpenGL version: %s", glGetString(GL_VERSION));

		RE_OGL(glEnable(GL_CULL_FACE));
		RE_OGL(glCullFace(GL_BACK));
		RE_OGL(glEnable(GL_DEPTH_TEST));
		RE_OGL(glDepthFunc(GL_LEQUAL));
	}

	Window::Window(int x, int y, int w, int h, const string &title, bool visible)
		:	x(x), y(y), w(w), h(h), title(title),
			was_windowed(true), visible(visible), focused(visible), wnd(nullptr),
			monitor(nullptr), frameBuffer()
	{
		wnd = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
		glfwSetWindowPos(wnd, x, y);
		modules::WindowManager::GetInst()->registerWindow(this);
		
		initGlew(*this);

		if(visible)
			show();
		else
			hide();
	}

	Window::Window(def_win_pos_t, int w, int h, const string &title, bool visible)
		:	x(), y(), w(w), h(h), title(title),
			was_windowed(true), visible(visible), focused(visible), wnd(nullptr),
			monitor(nullptr), frameBuffer()
	{
		wnd = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
		glfwGetWindowPos(wnd, &x, &y);
		modules::WindowManager::GetInst()->registerWindow(this);

		initGlew(*this);

		if(visible)
			show();
		else
			hide();
	}

	Window::Window(graphics::Monitor &monitor, const string &title, bool visible)
		:x(0), y(0), w(), h(), title(title),
		was_windowed(false), visible(visible), focused(visible), wnd(nullptr),
		monitor(&monitor), frameBuffer()
	{
		graphics::VideoMode mode;
		monitor.getCurrentVideoMode(&mode);

		w = mode.width;
		h = mode.height;
			
		wnd = glfwCreateWindow(mode.width, mode.height, title.c_str(), monitor.monitor, nullptr);
		modules::WindowManager::GetInst()->registerWindow(this);

		initGlew(*this);

		if(visible)
			show();
		else
			hide();
	}

	Window::~Window()
	{
		frameBuffer.destroy();
		if(wnd)
			glfwDestroyWindow(wnd);
		modules::WindowManager::GetInst()->unregisterWindow(this);
	}


	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(wnd) != 0;
	}
	void Window::close()
	{
		glfwSetWindowShouldClose(wnd, 1);
	}
		
	bool Window::isFullscreen() const
	{
		return monitor!=nullptr;
	}

	bool Window::isFocused() const
	{
		return focused;
	}


	void Window::getFramebufferSize(int *width, int *height) const
	{
		glfwGetFramebufferSize(wnd, width, height);
	}

	int Window::getWidth() const
	{
		if(monitor)
		{
			graphics::VideoMode m;
			monitor->getCurrentVideoMode(&m);
			return m.width;
		}
		return w;
	}
	int Window::getHeight() const
	{
		if(monitor)
		{
			graphics::VideoMode m;
			monitor->getCurrentVideoMode(&m);
			return m.height;
		}
		return h;
	}
	int Window::getX() const
	{
		if(monitor)
			return 0;
		return x;
	}
	int Window::getY() const
	{
		if(monitor)
			return 0;
		return y;
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

	math::vec2<double> Window::getCursorPos() const
	{
		math::vec2<double> pos;
		glfwGetCursorPos(wnd, &pos.x, &pos.y);
		return pos;
	}
	void Window::setCursorPos(const math::vec2<double> &pos)
	{
		glfwSetCursorPos(wnd, pos.x, pos.y);
	}
	void Window::setSize(int w, int h)
	{
		glfwSetWindowSize(wnd, w, h);
		this->w = w;
		this->h = h;
	}
	void Window::setPosition(int x, int y)
	{
		glfwSetWindowPos(wnd, x, y);
		this->x = x;
		this->y = y;
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

		this->onClose();
		glfwDestroyWindow(wnd);

		modules::WindowManager::GetInst()->unregisterWindow(this);

		graphics::VideoMode mode;
		monitor->getCurrentVideoMode(&mode);
		wnd = glfwCreateWindow(mode.width, mode.height, title.c_str(), monitor->monitor, nullptr);
		initGlew(*this);
		this->onCreate();
		
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

		this->onClose();
		glfwDestroyWindow(wnd);
		modules::WindowManager::GetInst()->unregisterWindow(this);
			
		wnd = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		w = width;
		h = height;
		if(!was_windowed)
			glfwGetWindowPos(wnd, &x, &y);
		else
			glfwSetWindowPos(wnd, x, y);
		
		initGlew(*this);
		this->onCreate();

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

	const graphics::FrameBuffer &Window::getFrameBuffer() const
	{
		return frameBuffer;
	}
	graphics::FrameBuffer &Window::getFrameBuffer()
	{
		return frameBuffer;
	}

	void Window::renderFrameBuffer() const
	{
		frameBuffer.unbind();
		graphics::Vertex verts[] = { graphics::Vertex(math::float3(0, 0, 0), math::float2(0, 0), math::float4(1, 0, 0, 1)),
			graphics::Vertex(math::float3(1, 0, 0), math::float2(1, 0), math::float4(0, 1, 0, 1)),
			graphics::Vertex(math::float3(0, 1, 0), math::float2(0, 1), math::float4(0, 1, 1, 1)),
			graphics::Vertex(math::float3(1, 0, 0), math::float2(1, 0), math::float4(0, 1, 0, 1)),
			graphics::Vertex(math::float3(1, 1, 0), math::float2(1, 1), math::float4(0, 0, 1, 1)),
			graphics::Vertex(math::float3(0, 1, 0), math::float2(0, 1), math::float4(0, 1, 1, 1))
		};

		graphics::VertexData model(graphics::RenderMode::RM_TRIANGLES,graphics::AllocationStrategy::AS_STATIC);
		model.alloc();
		model.setData(verts, _countof(verts));
		model.bind();
		model.draw();

	}

	void Window::onCharacter(uint codepoint) { }
	void Window::onCursorEnter(bool entered) { }
	void Window::onCursorMove(double x, double y) { }
	void Window::onKey(input::Key key, int scancode, bool pressed, int mods) { emit(input::KeyEvent(key, pressed)); }
	void Window::onMouseButton(input::Key button, bool pressed, int mods) { emit(input::KeyEvent(button, pressed)); }

	void Window::onFramebufferSizeChanged(int width, int height)
	{
		frameBuffer.setSize(width, height);
	}
	void Window::onClose() { }
	void Window::onFocusChanged(bool focus) { focused = focus; }
	void Window::onIconify(bool iconified) { }
	void Window::onPositionChanged(int x, int y) { }
	void Window::onRefresh() { }
	void Window::onSizeChanged(int width, int height) { }
	void Window::onCreate() { }
	void Window::onVisibilityChanged(bool newValue) { }
	void Window::onScroll(double xoffset, double yoffset) { }
}