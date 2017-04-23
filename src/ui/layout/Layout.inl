namespace re
{
	namespace ui
	{
		namespace layout
		{
			REIL math::Vec2<Repeat> const& Image::repeat() const
			{
				return m_repeat;
			}


			REIL void Borders::set_left_width(
				float width)
			{
				m_width.left = width;
			}
			REIL void Borders::set_right_width(
				float width)
			{
				m_width.right = width;
			}
			REIL void Borders::set_top_width(
				float width)
			{
				m_width.top = width;
			}
			REIL void Borders::set_bottom_width(
				float width)
			{
				m_width.bottom = width;
			}
			REIL void Borders::set_width(
				float width)
			{
				m_width = width;
			}

			REIL float Borders::left_width() const
			{
				return m_width.left;
			}
			REIL float Borders::right_width() const
			{
				return m_width.left;
			}
			REIL float Borders::top_width() const
			{
				return m_width.left;
			}
			REIL float Borders::bottom_width() const
			{
				return m_width.left;
			}
		}
	}
}