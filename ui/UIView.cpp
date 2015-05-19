#include "UIView.hpp"


namespace re
{
	namespace ui
	{
		math::fmat4x4 UIView::transformation() const
		{
			return math::fmat4x4::transformation(position, rotation, scaling);
		}

		math::STPlane<float> UIView::uiPlane() const
		{
			math::fmat4x4 transform = transformation();

			math::fvec3 o(math::fvec3(transform * math::fvec4(0, 0, 0, 1)));
			math::fvec3 s(transform * math::fvec4(1,0,0,0));
			math::fvec3 t(transform * math::fvec4(0,-1, 0, 0));

			return math::STPlane<float>(o, s, t);
		}

		void UIView::updateCursor(const math::Ray<float> &cursor)
		{
			math::fvec2 local;
			if(!math::intersect(cursor, uiPlane(), &local.x, &local.y, nullptr))
				content.onCursorLeave();
			else
				content.onCursorMove(math::fvec2(local.x, local.y) - content.position());
		}

		void UIView::updateCursor(const math::fvec2 &cursor)
		{
			content.onCursorMove(cursor-content.position());
		}

		const strong_handle<UIElement> &UIView::findElement(const string &name) const
		{
			return content.findChild(name);
		}
	}
}