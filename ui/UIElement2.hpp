#ifndef __re_ui_uielement2_hpp_defined
#define __re_ui_uielement2_hpp_defined

#include "../types.hpp"
#include "../math/Vector.hpp"
#include "../graphics/Texture.hpp"
#include "../graphics/VertexData.hpp"
#include "Label.hpp"
#include "layout/Layout.hpp"

namespace re
{
	namespace ui
	{
		class UIElement
		{
		protected:
			UIElement *parent;
			std::vector<strong_handle<UIElement>> children;

			string name;
			
			math::vec2<layout::Align> align;
			
			math::vec2<layout::Size> position;
			math::vec2<layout::Size> min_size;
			math::vec2<layout::Size> max_size;

			layout::Box<layout::Size> margin;
			layout::Box<layout::Size> padding;
			layout::Box<layout::Border> border;

			layout::Image background;

			Label label;

			math::vec2<layout::ScrollBar> scrollbars;

			mutable strong_handle<graphics::VertexData> background_model;
			mutable strong_handle<graphics::VertexData> border_model;

			mutable bool invalid_background_model;
			mutable bool invalid_border_model;
		private:
			mutable float temp_last_absolutecontentwidth,
				temp_last_absolutecontentheight;
			mutable bool invalid_width, invalid_height;
		public:
			UIElement();
			UIElement(const UIElement &) = delete;
			UIElement(UIElement && move);

			UIElement &operator=(const UIElement &) = delete;
			UIElement &operator=(UIElement && move);

			Label &getLabel();
			const Label &getLabel() const;

			const layout::Box<layout::Border> &getBorder() const;
			// invalidates the border model.
			void setBorder(const layout::Box<layout::Border> &border);

			const layout::Image &getBackground() const;
			void setBackground(const layout::Image &background);

			float absoluteMinWidth() const;
			float absoluteMinHeight() const;
			float absoluteMaxWidth() const;
			float absoluteMaxHeight() const;

			// the width of the area containing all children. unaffected by min / max width.
			float absoluteContentWidth() const;
			// the height of the care containing all children. unaffected by min / max height.
			float absoluteContentHeight() const;

			// the width of the content area. affected by min / max width.
			float absoluteContentAreaWidth() const;
			// the height of the content area. affected by min / max height.
			float absoluteContentAreaHeight() const;

			// the width of the content area, reduced by the width of the vertical scroll bars.
			float contentAreaDisplayWidth() const;
			// the height of the content area, reduced by the width of the horizontal scroll bars.
			float contentAreaDisplayHeight() const;
			
			bool visibleScrollBarH() const;
			bool visibleScrollBarV() const;

			float absoluteLeft() const;
			float absoluteTop() const;

			float absoluteMarginLeft() const;
			float absoluteMarginTop() const;
			float absoluteMarginRight() const;
			float absoluteMarginBottom() const;

			float absolutePaddingLeft() const;
			float absolutePaddingTop() const;
			float absolutePaddingRight() const;
			float absolutePaddingBottom() const;

			float absoluteBoxWidth() const;
			float absoluteBoxHeight() const;

		};
	}
}


#endif