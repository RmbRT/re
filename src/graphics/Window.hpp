#ifndef __re_window_hpp_defined
#define __re_window_hpp_defined

#include "../defines.hpp"
#include "../types.hpp"

#include <Lock/Lock.hpp>

#include "GL/Version.hpp"
#include "Monitor.hpp"
#include "../input/Input.hpp"
#include "GL/FrameBuffer.hpp"
#include "../math/Vector.hpp"

namespace re
{
	namespace graphics
	{
		/** This class is an object oriented binding for the glfw window class.
			It is extended with overridable callback events.
		@usage:
			Derive a class of Window to implement custom behaviour and receive window events.
		@note:
			When the Window is instantiated, a window will be created.
			Likewise, upon destruction, the window will also be closed.
			This should be kept in mind when specifying the lifetime of a Window instance.
		@note:
			Deriving classes should call onCreate in their constructors and onClose in their destructors. */
		class Window
		{
			thread_local static lock::ThreadSafe<Window *> current_context;
			/** The pointer pointing to this Window, if it is current.
				Used for releasing the old thread*/
			lock::ThreadSafe<Window *> * m_current_context_ptr;

			/** The Windows that share their contexts with this ones. */
			std::vector<Window *> m_context_slaves;
			/** The Window this instance shares its context with. If this Window owns its context, it is null. */
			Window * m_context_master;

			/** The Handle to the window. */
			struct NativeWindowHandle * m_handle;
			/** If this Window is in fullscreen mode, then this is a pointer to the Monitor used. */
			Monitor * m_monitor;
		public:
			/** Creates an empty Window handle.
				Create the Window with create(). */
			Window();
			/** Moves the ownership of the Window. */
			Window(Window &&);
			/** Moves the ownership of the Window. */
			Window &operator=(Window &&);
			/** Closes the Window. */
			~Window();

			/** Whether the Window exists. */
			RECX bool exists() const;

			/** Fetches whether the window was requested to be closed. */
			bool should_close() const;
				
			/** Checks whether the window is in fullscreen mode. */
			bool fullscreen() const;

			/** Returns whether the window is currently focused. */
			bool focused() const;

			/** Returns the size of the framebuffer associated with the window.
			This is not equal to the size of the window, but only of the drawing area/canvas.
			@param[out] width: the width of the framebuffer.
			@param[out] height: the height of the framebuffer. */
			void framebuffer_size(int * width, int * height) const;
				
			/** Returns the width of the window (window bounds). */
			int width() const;
				
			/** Returns the height of the window (window bounds). */
			int height() const;

			/** Returns the X coordinate of the window in screen coordinates. */
			int x() const;
			/** Returns the Y coordinate of the window in screen coordinates. */
			int y() const;

			/** Returns the title of the window. */
			const char* title() const;
				
			/** Returns whether the window is visible or not. */
			bool visible() const;

		protected:

			/** Creates the Window handle with the given arguments.
			@assert The Window must not exist yet.
			@param[in] w, h: The size of the Window, in screen coordinates.
			@param[in] title: The title of the Window.
			@param[in] visible: Whether the Window should be visible upon creation.
			@param[in] share_context: A Window to share the GPU context with, or null. */
			/** @param[in] x, y: The position of the Window, in screen coordinates. */
			void create(int x, int y, int w, int h, string title, bool visible, Window * share_context);
			/** Uses the OS default Window position. */
			void create(int w, int h, string title, bool visible, Window * share_context);
			/** Creates a fullscreen Window.
			@param[in] monitor: When creating a fullscreen Window, a Monitor must be used as target. */
			void create(Monitor & monitor, int w, int h, bool visible, Window * share_context);
			/**@}*/

			/** Makes the window visible. */
			void show();
				
			/** Makes the window invisible. */
			void hide();

			/** Requests the window to close. */
			void close();
			
			/** Returns the Cursor position relative to the client area of the window.
			@return: the Cursor position relative to the client are of the window, in screen coordinates. */
			math::vec2<double> cursor() const;
			/** Sets the Cursor position relative to the client area of the window.
			@param[in] pos: the new Cursor position relative to the client area of the window, in screen coordinates. */
			void set_cursor(const math::vec2<double> &pos);

			/** Sets the position of the window.
			@param[in] x: the X coordinate of the client area of the window, in screen coordinates.
			@param[in] y: the Y coordinate of the client area of the window, in screen coordinates. */
			void set_position(int x, int y);
			/** Sets the size of the window.
			@param[in] w: the width of the client area of the window, in screen coordinates.
			@param[in] h: the height of the client area of the window, in screen coordinates. */
			void set_size(int w, int h);

			/** Sets the title of the window.
			@param[in] title: the title of the window. */
			void set_title(string title);

			/** Makes the context of the window current, enabling rendering to the window. */
			void make_context_current();

			/** Swaps the background and the foreground buffers. */
			void swapBuffers();
		private:

			/** Called when the Window receives an unicode character.
			@param[in] codepoint: the unicode value of the character. */
			virtual void onCharacter(uint codepoint) = 0;
				
			/** Called when the cursor enters or leaves the window.
			@param[in] entered: true if the cursor entered, false if it left the window. */
			virtual void onCursorEnter(bool entered) = 0;
				
			/** Called when the cursor moves.
			@param[in] x: the x coordinate of the cursor, relative to the top left corner of the window (in pixels).
			@param[in] y: the y coordinate of the cursor, relative to the top left corner of the window (in pixels). */
			virtual void onCursorMove(double x, double y) = 0;

			/** Called when a key is pressed, released, or repeated.
			@param[in] key: the virtual key code of the key.
			@param[in] scancode: the scancode the key has on the keyboard.
			@param[in] pressed: whether the key was pressed or released.
			@param[in] mods: modifier key flags.
			@note:
				The default implementation calls re::messaging::Emitter<re::input::KeyEvent>::emit(key, pressed).*/
			virtual void onKey(input::Key key, int scancode, bool pressed, int mods) = 0;

			/** Called when a mouse button is pressed or released.
			@param[in] button: the button that was pressed or released.
			@param[in] action: whether the button was pressed or released.
			@param[in] mods: modifier key flags.
			@note:
				The default implementation calls re::messaging::Emitter<re::input::KeyEvent>::emit(button, pressed). */
			virtual void onMouseButton(input::Key button, bool pressed, int mods) = 0;

			/** Called when the size of the framebuffer changed.
			@param[in] width: the new width (in pixels) of the framebuffer.
			@param[in] height: the new height (in pixels) of the framebuffer. */
			virtual void onFramebufferSizeChanged(int width, int height) = 0;

			/** Called when the window close button was clicked or the destructor is called. */
			virtual void onClose() = 0;

			/** Called when the window gains or looses focus.
			@param[in] focus: true if the window gained focus, false if it lost focus. */
			virtual void onFocusChanged(bool focus) = 0;

			/** Called when the window becomes minimized or restored.
			@param[in] iconified: true if the window was minimized, false if it was restored. */
			virtual void onIconify(bool iconified) = 0;
				
			/** Called when the window position changes.
			@param[in] x: the new window x coordinate (in pixels).
			@param[in] y: the new window y coordinate (in pixels). */
			virtual void onPositionChanged(int x, int y) = 0;

			/** Called when the window should refresh.*/
			virtual void onRefresh() = 0;

			/** Called when the window got resized.
			@param[in] width: the new width of the window.
			@param[in] height: the new height of the window. */
			virtual void onSizeChanged(int width, int height) = 0;

			/** Called when the window was created.*/
			virtual void onCreate() = 0;

			/** Gets called by Window::show() and Window::hide().
			@param[in] shown: true if the window became visible, false if it became hidden. */
			virtual void onVisibilityChanged(bool shown) = 0;
				
			/** Gets called upon scrolling.
			@param[in] xoffset: the amount of pixels scrolled in x axis.
			@param[in] yoffset: the amount of pixels scrolled in y axis. */
			virtual void onScroll(double xoffset, double yoffset) = 0;



			/** Destroys the Window handle.
			@assert The Window must exist. */
			void destroy();
			/** Invalidates the Window, so that no data is released twice. */
			void invalidate();
		};
	}
}

#endif