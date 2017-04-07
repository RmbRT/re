#ifndef __re_window_hpp_defined
#define __re_window_hpp_defined

#include "../defines.hpp"
#include "../types.hpp"

#include <Lock/Lock.hpp>

#include "gl/Version.hpp"
#include "Monitor.hpp"
#include "../input/Input.hpp"
#include "gl/Context.hpp"
#include "../math/Vector.hpp"
#include "../math/Rect.hpp"
#include "Hints.hpp"

namespace re
{
	namespace graphics
	{
		/** This class is an object oriented binding for the glfw window class.
			It is extended with overridable callback events.
		@usage:
			Derive a class of Window to implement custom behaviour and receive window events.
			GPU data should be stored in the Context. Create a custom Context by overriding create_context(). */
		class Window : gl::ContextReferenceCounter
		{
			/** The Context of the Window.
			Only the Window that is pointed back to by the Context owns the Context. */
			gl::Context * m_context;

			/** The Handle to the window. */
			struct GLFWwindow * m_handle;

			/** If this Window is in fullscreen mode, then this is a pointer to the Monitor used. */
			Monitor * m_monitor;

			/** The title of the Window. */
			string8_t m_title;
			/** The Window bounds in screen coordinates. */
			math::Rect<int> m_screen_bounds;
			/** The Window size in pixels. */
			math::int2_t m_pixels;
			/** Whether the Window is visible or hidden. */
			bool m_visible;
			/** Whether the Window is focused for input. */
			bool m_focused;
			/** Whether the Window is iconified. */
			bool m_iconified;
			/** The cursor positon relative to the Window, in screen coordinates. */
			math::double2_t m_cursor;

			/** The WindowHints used when creating the Window. */
			WindowHints m_window_hints;
			/** The FramebufferHints used when creating the Window. */
			FramebufferHints m_framebuffer_hints;
		public:
			/** Creates an empty Window handle. */
			Window();
			/** Moves the ownership of the Window. */
			Window(Window &&);
			/** Moves the ownership of the Window. */
			Window &operator=(Window &&);
			/** Closes the Window, if it exists. */
			~Window();

			/** Whether the Window exists. */
			REIL bool exists() const;

			/** Whether the Window is in fullscreen mode.
			@assert The Window must exist. */
			REIL bool fullscreen() const;

			/** Whether the Window is currently focused.
			@assert The Window must exist. */
			REIL bool focused() const;

			/** Whether the Window is currently iconified.
			@assert The Window must exist. */
			REIL bool iconified() const;

			/** Returns the size of the framebuffer associated with the window, in pixels.
			This is not equal to the size of the window, but only of the drawing area/canvas.
			@assert The Window must exist. */
			REIL math::int2_t const& pixels() const;

			/** Returns the Window bounds (in screen coordinates).
			@assert The Window must exist. */
			REIL math::Rect<int> const& screen_bounds() const;

			/** Returns the title of the window.
			@assert The Window must exist. */
			REIL string8_t const& title() const;

			/** Returns whether the window is visible or not.
			@assert The Window must exist. */
			REIL bool visible() const;

			/** Returns the Cursor position relative to the client area of the window.
			@return
				the Cursor position relative to the client are of the window, in screen coordinates. */
			REIL math::double2_t const& cursor() const;

			/** Requests the Window to close.
				Calls onCloseRequest, and if the close request was accepted, closes the Window. */
			void request_close();

			/** Returns the Context of the Window.
			@assert The Window must exist. */
			REIL gl::Context & context();
			/** Returns the Context of the Window.
			@assert The Window must exist. */
			REIL gl::Context const& context() const;

		protected:

			/** Creates the Window handle with the given arguments.
			@assert The Window must not yet exist.
			@param[in] window:
				The hints controlling the Window creation.
			@param[in] framebuffer:
				The hints controlling the framebuffer creation.
			@param[in] context:
				The hints controlling the Context creation.
			@return
				Whether the Window was created successfully. */
			bool create(
				string8_t title,
				WindowHints const& window,
				FramebufferHints const& framebuffer,
				gl::ContextHints const& context);

			/** Creates the Window and shares the Context with the given Window.
			@assert The Window must not yet exist.
			@param[in] hints:
				The hints controllin. */
			bool create(
				string8_t title,
				WindowHints const& window,
				FramebufferHints const& framebuffer,
				Window const& share_context);

			/** Recreates the Window handle, keeping the old context.
			@assert The Window must exist.
			@param[in] window:
				The new WindowHints.
			@param[in] framebuffer:
				The new FramebufferHints.
			@return
				Whether the new Window could be created. If it failed, the old window is kept. */
			bool recreate(
				string8_t title,
				WindowHints const& window,
				FramebufferHints const& framebuffer);

			/** Destroys the Window handle.
			@assert The Window must exist. */
			void destroy();

			/** Makes the window visible. */
			void show();

			/** Makes the window invisible. */
			void hide();

			/** Sets the Cursor position relative to the client area of the window.
			@param[in] pos:
				the new Cursor position relative to the client area of the window, in screen coordinates. */
			void set_cursor(math::double2_t const& pos);

			/** Sets the position of the window.
			@param[in] x:
				the X coordinate of the client area of the window, in screen coordinates.
			@param[in] y:
				the Y coordinate of the client area of the window, in screen coordinates. */
			void set_position(int x, int y);
			/** Sets the size of the window.
			@param[in] w:
				the width of the client area of the window, in screen coordinates.
			@param[in] h:
				the height of the client area of the window, in screen coordinates. */
			void set_size(int w, int h);

			/** Sets the title of the window.
			@param[in] title:
				the title of the window. */
			void set_title(string8_t title);

			/** Makes the context of the window current, enabling rendering to the window.
			@assert The Window must exist. */
			void make_context_current();

			/** Swaps the background and the foreground buffers.
			@assert The Window must exist. */
			void swap_buffers();

			/** Processes all waiting events. */
			static void poll_events();

			/** Pauses the current thread until an event occurs, and processes it.
				If events wait already, processes them directly. */
			static void wait_events();
		private:

			/** Creates the correct Context used by this Window.
				Called by create(). */
			virtual gl::Context * create_context(
				gl::ContextHints const&,
				gl::Version const&) = 0;

			/** Called when the Window receives an unicode character.
			@param[in] codepoint:
				the unicode value of the character. */
			virtual void onCharacter(uint_t codepoint) = 0;

			/** Called when the cursor enters or leaves the window.
			@param[in] entered:
				true if the cursor entered, false if it left the window. */
			virtual void onCursorEnter(bool entered) = 0;

			/** Called when the cursor moves.
			@param[in] x:
				the x coordinate of the cursor, relative to the top left corner of the window (in pixels).
			@param[in] y:
				the y coordinate of the cursor, relative to the top left corner of the window (in pixels). */
			virtual void onCursorMove(double x, double y) = 0;

			/** Called when a key is pressed, released, or repeated.
			@param[in] key:
				the virtual key code of the key.
			@param[in] scancode:
				the scancode the key has on the keyboard.
			@param[in] pressed:
				whether the key was pressed or released.
			@param[in] mods:
				modifier key flags.
			@note:
				The default implementation calls re::messaging::Emitter<re::input::KeyEvent>::emit(key, pressed). */
			virtual void onKey(input::Key key, int scancode, bool pressed, int mods) = 0;

			/** Called when a mouse button is pressed or released.
			@param[in] button:
				the button that was pressed or released.
			@param[in] action:
				whether the button was pressed or released.
			@param[in] mods:
				modifier key flags.
			@note:
				The default implementation calls re::messaging::Emitter<re::input::KeyEvent>::emit(button, pressed). */
			virtual void onMouseButton(input::Key button, bool pressed, int mods) = 0;

			/** Called when the size of the framebuffer changed.
			@param[in] width:
				the new width (in pixels) of the framebuffer.
			@param[in] height:
				the new height (in pixels) of the framebuffer. */
			virtual void onFramebufferSizeChanged(int width, int height) = 0;

			/** Called when the user attempts to close the Window.
				Use this function to decide how the Window reacts when the user requests it to close.
				If the close request is accepted, the Window is destroyed afterwards.
			@return
				True, if the close request should be accepted, and false, if denied. */
			virtual bool onCloseRequest() = 0;

			/** Called when the window gains or looses focus.
			@param[in] focus:
				true if the window gained focus, false if it lost focus. */
			virtual void onFocusChanged(bool focus) = 0;

			/** Called when the window becomes minimized or restored.
			@param[in] iconified:
				true if the window was minimized, false if it was restored. */
			virtual void onIconify(bool iconified) = 0;

			/** Called when the window position changes.
			@param[in] x:
				the new window x coordinate (in pixels).
			@param[in] y:
				the new window y coordinate (in pixels). */
			virtual void onPositionChanged(int x, int y) = 0;

			/** Called when the window should refresh. */
			virtual void onRefresh() = 0;

			/** Called when the window got resized.
			@param[in] width:
				the new width of the window.
			@param[in] height:
				the new height of the window. */
			virtual void onSizeChanged(int width, int height) = 0;

			/** Gets called by Window::show() and Window::hide().
			@param[in] shown:
				true if the window became visible, false if it became hidden. */
			virtual void onVisibilityChanged(bool shown) = 0;

			/** Gets called upon scrolling.
			@param[in] xoffset:
				the amount of pixels scrolled in x axis.
			@param[in] yoffset:
				the amount of pixels scrolled in y axis. */
			virtual void onScroll(double xoffset, double yoffset) = 0;
		};
	}
}

#include "Window.inl"

#endif