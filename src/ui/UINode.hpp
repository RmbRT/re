#ifndef __re_ui_uielement2_hpp_defined
#define __re_ui_uielement2_hpp_defined

#include "../types.hpp"
#include "../math/Vector.hpp"
#include "../graphics/Texture.hpp"
#include "../graphics/VertexData.hpp"
#include "Label.hpp"
#include "layout/Layout.hpp"
#include "../graphics/RenderSession.hpp"

namespace re
{
	namespace ui
	{
		/*The base class for all UI elements.
		Contains a Box Model representation, similar to the one found in HTML / CSS.
		Contains a list of UINodes as children.
		@usage:
			Deriving classes should override the method @[updateModels] to create a custom look.*/
		class UINode
		{
		protected:
			UINode *parent;
			
			strong_handle<UINode> prev_sibling;
			strong_handle<UINode> next_sibling;

			std::vector<strong_handle<UINode>> children;

			string name;
			
			strong_handle<Font> font;

			math::vec2<layout::Align> align;
			
			math::vec2<layout::Size> position;
			math::vec2<layout::Size> min_size;
			math::vec2<layout::Size> max_size;

			layout::Box<layout::Size> margin;
			layout::Box<layout::Size> padding;
			layout::Box<layout::Border> border;

			layout::Image border_corner_top_left,
				border_corner_top_right,
				border_corner_bottom_left,
				border_corner_bottom_right;

			strong_handle<graphics::VertexData>
				border_corner_top_left_model,
				border_corner_top_right_model,
				border_corner_bottom_left_model,
				border_corner_bottom_right_model;

			layout::Image background;

			layout::Display display;

			math::vec2<layout::ScrollBar> scrollbars;

			mutable strong_handle<graphics::VertexData> background_model;
			mutable strong_handle<graphics::VertexData> border_model;
			mutable strong_handle<graphics::VertexData> border_corner_model;

			mutable bool invalid_background_model;
			mutable bool invalid_border_model;
			mutable bool invalid_children;

			// invalidates the calculated width and height, and the border and background models, and the children.
			void contentChanged() const;

			// called by @[update].
			virtual void updateModels() const;
			virtual void updateBorderModel() const;
			virtual void updateBackgroundModel() const;

		private:
			// Used to prevent an infinite recursion when resolving percentage based size values.
			mutable float temp_last_absolute_content_width, temp_last_absolute_content_height;
			// Indicates that the size values should be updated.
			mutable bool invalid_width, invalid_height;
		public:
			UINode();
			UINode(const UINode &) = delete;
			UINode(UINode && move);

			virtual ~UINode() {}


			UINode &operator=(const UINode &) = delete;
			UINode &operator=(UINode && move);

			// updates contents of the children and this node.
			virtual void update();
			virtual void draw(graphics::RenderSession &session) const;

			/// Content

			void setFont(const strong_handle<Font> &font);
			const strong_handle<Font> &getFont() const;

			const std::vector<strong_handle<UINode>> &getChildren() const;
			// node must not be a child of any other UINode already.
			void addChild(const strong_handle<UINode> &node);

			strong_handle<UINode> findChild(const string &name) const;
			
			
			/// Box Model

			// returns the border of the UiNode.
			const layout::Box<layout::Border> &getBorder() const;
			// invalidates the border model.
			void setBorder(const layout::Box<layout::Border> &border);

			const layout::Image &getBackground() const;
			// sets the background image and invalidates the background model.
			void setBackground(const layout::Image &background);

			// resolves the minimal width of this UINode.
			float absoluteMinWidth() const;
			// resolves the minimal height of this UINode.
			float absoluteMinHeight() const;
			// resolves the maximal width of this UINode.
			float absoluteMaxWidth() const;
			// resolves the maximal height of this UINode.
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
			
			// checks whether the horizontal scroll bar is visible.
			bool visibleScrollBarH() const;
			// checks whether the vertical scroll bar is visible.
			bool visibleScrollBarV() const;

			// resolves the offset on the horizontal axis.
			float absoluteLeft() const;
			// resolves the offset on the vertical axis.
			float absoluteTop() const;

			// resolves the left margin.
			float absoluteMarginLeft() const;
			// resolves the top margin.
			float absoluteMarginTop() const;
			// resolves the right margin.
			float absoluteMarginRight() const;
			// resolves the bottom margin.
			float absoluteMarginBottom() const;

			// resolves the left padding.
			float absolutePaddingLeft() const;
			// resolves the top padding.
			float absolutePaddingTop() const;
			// resolves the right padding.
			float absolutePaddingRight() const;
			// resolves the bottom padding.
			float absolutePaddingBottom() const;

			/*Resolves the width of the whole box.
			This contains the border, margin, padding, and content area.*/
			float absoluteBoxWidth() const;
			/*Resolves the height of the whole box.
			This contains the border, margin, padding, and content area.*/
			float absoluteBoxHeight() const;

			// calculates the position of this UINode relative to its parents origin.
			math::fvec2 absolutePosition() const;

			void setMinWidth(const layout::Size &min_w);
			void setMinHeight(const layout::Size &min_h);
			void setMaxWidth(const layout::Size &max_w);
			void setMaxHeight(const layout::Size &max_h);
			// sets both min and max width to <width>
			void setWidth(const layout::Size &width);
			// sets both min and max height to <height>
			void setHeight(const layout::Size &height);

			void setMargin(const layout::Box<layout::Size> &margin);
			void setMarginLeft(const layout::Size &margin);
			void setMarginRight(const layout::Size &margin);
			void setMarginTop(const layout::Size &margin);
			void setMarginBottom(const layout::Size &margin);

			void setPadding(const layout::Box<layout::Size> &padding);
			void setPaddingLeft(const layout::Size &padding);
			void setPaddingTop(const layout::Size &padding);
			void setPaddingRight(const layout::Size &padding);
			void setPaddingBottom(const layout::Size &padding);

			void setBorderLeft(const layout::Border &border);
			void setBorderTop(const layout::Border &border);
			void setBorderRight(const layout::Border &border);
			void setBorderBottom(const layout::Border &border);

			void setBorderTopLeftCorner(const layout::Image &corner);
			void setBorderTopRightCorner(const layout::Image &corner);
			void setBorderBottomLeftCorner(const layout::Image &corner);
			void setBorderBottomRightCorner(const layout::Image &corner);

			void setLeft(const layout::Size &left);
			void setTop(const layout::Size &top);


		};
	}
}


#endif