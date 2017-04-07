namespace re
{
	namespace graphics
	{
		bool Window::exists() const
		{
			return m_handle != nullptr;
		}

		bool Window::fullscreen() const
		{
			RE_DBG_ASSERT(exists() && "Tried reading properties of nonexisting Window.");
			return m_monitor != nullptr;
		}

		bool Window::focused() const
		{
			RE_DBG_ASSERT(exists() && "Tried reading properties of nonexisting Window.");
			return m_focused;
		}

		bool Window::iconified() const
		{
			RE_DBG_ASSERT(exists() && "Tried reading properties of nonexisting Window.");
			return m_iconified;
		}

		math::int2_t const& Window::pixels() const
		{
			RE_DBG_ASSERT(exists() && "Tried reading properties of nonexisting Window.");
			return m_pixels;
		}

		math::Rect<int> const& Window::screen_bounds() const
		{
			RE_DBG_ASSERT(exists() && "Tried reading properties of nonexisting Window.");
			return m_screen_bounds;
		}

		string8_t const& Window::title() const
		{
			RE_DBG_ASSERT(exists() && "Tried reading properties of nonexisting Window.");
			return m_title;
		}

		bool Window::visible() const
		{
			RE_DBG_ASSERT(exists() && "Tried reading properties of nonexisting Window.");
			return m_visible;
		}

		math::double2_t const& Window::cursor() const
		{
			RE_DBG_ASSERT(exists() && "Tried reading properties of nonexisting Window.");
			return m_cursor;
		}

		gl::Context & Window::context()
		{
			RE_DBG_ASSERT(exists() && "Tried reading properties of nonexisting Window.");
			return *m_context;
		}

		gl::Context const& Window::context() const
		{
			RE_DBG_ASSERT(exists() && "Tried reading properties of nonexisting Window.");
			return *m_context;
		}
	}
}