#include "UIView.hpp"


namespace re
{
	namespace ui
	{
		math::fmat4x4_t UIView::transformation() const
		{
			return math::fmat4x4_t::transformation(position, rotation, scaling);
		}

		math::STPlane<float> UIView::ui_plane() const
		{
			math::fmat4x4_t transform = transformation();

			math::fvec3_t o(math::fvec3_t(transform * math::fvec4_t(0, 0, 0, 1)));
			math::fvec3_t s(transform * math::fvec4_t(1,0,0,0));
			math::fvec3_t t(transform * math::fvec4_t(0,-1, 0, 0));

			return math::STPlane<float>(o, s, t);
		}

		void UIView::update_cursor(
			math::Ray<float> const& cursor)
		{
			math::fvec2_t local;
			if(!math::intersect(
				cursor,
				ui_plane(),
				&local.x,
				&local.y,
				nullptr))
				content->on_cursor_leave();
			else
				content->on_cursor_move(math::fvec2_t(local.x, local.y) - content->absolute_position());
		}

		void UIView::update_cursor(math::fvec2_t const& cursor)
		{
			content->on_cursor_move(cursor-content->absolute_position());
		}

		UINode * UIView::find_node(string8_t const& name) const
		{
			return content->find_child(name.c_str());
		}
	}
}