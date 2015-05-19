#ifndef __re_window_hpp_defined
#define __re_window_hpp_defined

#include "..\types.hpp"

#include <string>
#define GLFW_INCLUDE_NONE
#include <glfw\glfw3.h>
#include "Monitor.hpp"
#include "..\input\Keyboard.hpp"

namespace re
{
	namespace modules { class WindowManager; }
	namespace graphics
	{
		const struct def_win_pos_t {} DEF_WIN_POS;
		/*This class is an object oriented binding for the glfw window class.
		It is extended with overridable callback events.
		@usage
			Upon creation, a window is created and is registered at the @{re::modules::WindowManager}.
			Derive a class of @{re::graphics::Window} to implement custom behaviour and receive window events.
		@note
			When the @{re::graphics::Window} is instantiated, a window will be created.
			Likewise, upon destruction, the window will also be closed.
			This should be kept in mind when specifying the lifetime of a @{re::graphics::Window} instance.*/
		class Window
		{	friend class re::modules::WindowManager;

			int x, y,
				w, h;
			bool was_windowed;
			bool visible;
			string title;
			GLFWwindow *wnd;
			Monitor *monitor;

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
			Window(Monitor &monitor, const string &title, bool visible);

			/*Destroys the instance and the associated window.*/
			~Window();

			/*Fetches whether the window was requested to be closed.*/
			bool shouldClose() const;
			
			/*Checks whether the window is in fullscreen mode.*/
			bool isFullscreen() const;
			
			/*Returns the size of the framebuffer associated with the window.
			This is not equal to the size of the window, but only of the drawing area/canvas.
			@param[out] width: the width of the framebuffer.
			@param[out] height: the height of the framebuffer.*/
			void getFramebufferSize(int *width, int *height) const;
			
			/*Returns the width of the window (window bounds).*/
			int getWidth() const;
			
			/*Returns the height of the window (window bounds).*/
			int getHeight() const;
			
			/*Makes the window visible.*/
			void show();
			
			/*Makes the window invisible.*/
			void hide();
			
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
			@[re::graphics::Window::getInternalWidth] and @[re::graphics::Window::getInternalHeight]
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
			@param[in] action: whether the key was pressed, released, or repeated.
			@param[in] mods: modifier key flags.*/
			virtual void onKey(int key, int scancode, input::KeyAction action, int mods);
			
			/*Called when a mouse button is pressed, released, or repeated.
			@param[in] button: the button that was pressed, released, or repeated.
			@param[in] action: whether the button was pressed, released, or repeated.
			@param[in] mods: modifier key flags.*/
			virtual void onMouseButton(input::MouseButton button, input::KeyAction action, int mods);

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
}

#endif