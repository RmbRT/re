#ifndef __re_window_hpp_defined
#define __re_window_hpp_defined

#include "types.hpp"

#include <string>
#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>
#undef GLFW_INCLUDE_NONE
#include "graphics/Monitor.hpp"
#include "input/Input.hpp"
#include "types.hpp"
#include "graphics/FrameBuffer.hpp"
#include "messaging/Emitter.hpp"
#include "math/Vector.hpp"

namespace re
{
	namespace modules { class WindowManager; }
	/*Used for constructing windows at the default window position assigned by the OS.*/
	const struct def_win_pos_t {} def_win_pos;
	

	/*This class is an object oriented binding for the glfw window class.
	It is extended with overridable callback events.
	@usage:
		Upon creation, a window is created and is registered at the @{re::modules::WindowManager}.
		Derive a class of @{re::graphics::Window} to implement custom behaviour and receive window events.
	@note:
		When the @{re::graphics::Window} is instantiated, a window will be created.
		Likewise, upon destruction, the window will also be closed.
		This should be kept in mind when specifying the lifetime of a @{re::Window} instance.
	@note:
		Deriving classes should call @[onCreate] in their constructors and @[onClose] in their destructors.*/
	class Window : public messaging::Emitter<input::KeyEvent>
	{	friend class re::modules::WindowManager;

	protected:
		int x, y,
			w, h;
		bool was_windowed;
		bool visible;
		bool focused;
		string title;
		GLFWwindow *wnd;
		graphics::Monitor *monitor;
		graphics::FrameBuffer frameBuffer;

	public:
		/*Initializes a window with the given arguments.
		@x,y,w,h: the bounds of the window.
		@title: the window's title.
		@visible: whether the window should be shown on creation.*/
		Window(int x, int y, int w, int h, const string &title, bool visible);
			
		/*Initializes a window at the default window position with the given arguments.
		@w,h: the window's size.
		@title: the window's title.
		@visible: whether the window should be shown on creation.*/
		Window(def_win_pos_t, int w, int h, const string &title, bool visible);
			
		/*Initializes a fullscreen window with the given arguments.
		@monitor: the monitor to use for the window.
		@title: the title of the window.
		@visible: whether the window should be shown on creation.*/
		Window(graphics::Monitor &monitor, const string &title, bool visible);

		/*Destroys the instance and the associated window.*/
		virtual ~Window();

		/*Fetches whether the window was requested to be closed.*/
		bool shouldClose() const;
		/*Requests the window to close.*/
		void close();
			
		/*Checks whether the window is in fullscreen mode.*/
		bool isFullscreen() const;

		/*Returns whether the window is currently focused.*/
		bool isFocused() const;

		/*Returns the size of the framebuffer associated with the window.
		This is not equal to the size of the window, but only of the drawing area/canvas.
		@param[out] width: the width of the framebuffer.
		@param[out] height: the height of the framebuffer.*/
		void getFramebufferSize(int *width, int *height) const;
			
		/*Returns the width of the window (window bounds).*/
		int getWidth() const;
			
		/*Returns the height of the window (window bounds).*/
		int getHeight() const;

		/*Returns the X coordinate of the window in screen coordinates.*/
		int getX() const;
		/*Returns the Y coordinate of the window in screen coordinates.*/
		int getY() const;

		/*Makes the window visible.*/
		void show();
			
		/*Makes the window invisible.*/
		void hide();
		
		/*Returns the Cursor position relative to the client area of the window.
		@return: the Cursor position relative to the client are of the window, in screen coordinates.*/
		math::vec2<double> getCursorPos() const;
		/*Sets the Cursor position relative to the client area of the window.
		@param[in] pos: the new Cursor position relative to the client area of the window, in screen coordinates.*/
		void setCursorPos(const math::vec2<double> &pos);

		/*Sets the position of the window.
		@param[in] x: the X coordinate of the client area of the window, in screen coordinates.
		@param[in] y: the Y coordinate of the client area of the window, in screen coordinates.*/
		void setPosition(int x, int y);
		/*Sets the size of the window.
		@param[in] w: the width of the client area of the window, in screen coordinates.
		@param[in] h: the height of the client area of the window, in screen coordinates.*/
		void setSize(int w, int h);

		/*Sets the title of the window.
		@param[in] title: the title of the window.*/
		void setTitle(const string &title);
		
		/*Returns the title of the window.*/
		const char* getTitle() const;
			
		/*Returns whether the window is visible or not.*/
		bool isVisible() const;

		/*Makes the context of the window current, enabling rendering to the window.*/
		void makeContextCurrent();

		/*Swaps the background and the foreground buffers.*/
		void swapBuffers();

		/*Destroys the window and creates a fullscreen window at the given monitor.
		The old window width and height, as well as position will remain internally.
		@param[in] monitor:
			The monitor to use for the fullscreen window.
			If null, then this function will do nothing.*/
		void switchToFullscreen(graphics::Monitor *monitor);
			
		/*Destroys the fullscreen window and creates a new window.
		If the window has already been in windowed state before, the window will be located
		at the old position of the window while it was in the windowed state.
		@[re::Window::getInternalWidth] and @[re::Window::getInternalHeight]
		can be used to make the new window have the same position and size as the old window.
		@param[in] width: the width of the window.
		@param[in] height: the height of the window.*/
		void switchToWindowed(int width, int height);

		/*Returns whether the window has already been in windowed state before.
		This is used for restoring the old position of the window after changing back from fullscreen mode.*/
		bool wasWindowed() const;
			
		/*Returns the internal width of the window.
		If the window has been in windowed state, the windowed width will be returned.*/
		int getInternalWidth() const;
		/*Returns the internal height of the window.
		If the window has been in windowed state, the windowed height will be returned.*/
		int getInternalHeight() const;

		/*Returns the framebuffer that is rendered into.*/
		const graphics::FrameBuffer &getFrameBuffer() const;
		graphics:: FrameBuffer &getFrameBuffer();

		virtual void renderFrameBuffer() const;
	private:

		/*Called when the Window receives an unicode character.
		@param[in] codepoint: the unicode value of the character.*/
		virtual void onCharacter(uint codepoint);
			
		/*Called when the cursor enters or leaves the window.
		@param[in] entered: true if the cursor entered, false if it left the window.*/
		virtual void onCursorEnter(bool entered);
			
		/*Called when the cursor moves.
		@param[in] x: the x coordinate of the cursor, relative to the top left corner of the window (in pixels).
		@param[in] y: the y coordinate of the cursor, relative to the top left corner of the window (in pixels).*/
		virtual void onCursorMove(double x, double y);

		/*Called when a key is pressed, released, or repeated.
		@param[in] key: the virtual key code of the key.
		@param[in] scancode: the scancode the key has on the keyboard.
		@param[in] pressed: whether the key was pressed or released.
		@param[in] mods: modifier key flags.
		@note:
			The default implementation calls re::messaging::Emitter<re::input::KeyEvent>::emit(key, pressed).*/
		virtual void onKey(input::Key key, int scancode, bool pressed, int mods);
			
		/*Called when a mouse button is pressed or released.
		@param[in] button: the button that was pressed or released.
		@param[in] action: whether the button was pressed or released.
		@param[in] mods: modifier key flags.
		@note:
			The default implementation calls re::messaging::Emitter<re::input::KeyEvent>::emit(button, pressed).*/
		virtual void onMouseButton(input::Key button, bool pressed, int mods);

		/*Called when the size of the framebuffer changed.
		@param[in] width: the new width (in pixels) of the framebuffer.
		@param[in] height: the new height (in pixels) of the framebuffer.*/
		virtual void onFramebufferSizeChanged(int width, int height);

		/*Called when the window close button was clicked or the destructor is called.*/
		virtual void onClose();

		/*Called when the window gains or looses focus.
		@param[in] focus: true if the window gained focus, false if it lost focus.*/
		virtual void onFocusChanged(bool focus);

		/*Called when the window becomes minimized or restored.
		@param[in] iconified: true if the window was minimized, false if it was restored.*/
		virtual void onIconify(bool iconified);
			
		/*Called when the window position changes.
		@param[in] x: the new window x coordinate (in pixels).
		@param[in] y: the new window y coordinate (in pixels).*/
		virtual void onPositionChanged(int x, int y);

		/*Called when the window should refresh.*/
		virtual void onRefresh();

		/*Called when the window got resized.
		@param[in] width: the new width of the window.
		@param[in] height: the new height of the window.*/
		virtual void onSizeChanged(int width, int height);

		/*Called when the window was created.*/
		virtual void onCreate();

		/*Gets called by Window::show() and Window::hide().
		@param[in] shown: true if the window became visible, false if it became hidden.*/
		virtual void onVisibilityChanged(bool shown);
			
		/*Gets called upon scrolling.
		@param[in] xoffset: the amount of pixels scrolled in x axis.
		@param[in] yoffset: the amount of pixels scrolled in y axis.*/
		virtual void onScroll(double xoffset, double yoffset);
	};
}

#endif