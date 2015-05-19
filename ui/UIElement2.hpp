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
		/*The base class for all UI elements.
		Contains a Box Model representation, similar to the one found in HTML / CSS.
		Contains a Label for text.
		Contains a list of UIElements as children.
		@usage:
			Deriving classes should override the method @[updateModels] to create a custom look.*/
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
			mutable bool invalid_children;

			// invalidates the calculated width and height, and the border and background models, and the children.
			void contentChanged() const;

			// called by @[update].
			virtual void updateModels();

		private:
			// Used to prevent an infinite recursion when resolving percentage based size values.
			mutable float temp_last_absolute_content_width, temp_last_absolute_content_height;
			// Indicates that the size values should be updated.
			mutable bool invalid_width, invalid_height;
		public:
			UIElement();
			UIElement(const UIElement &) = delete;
			UIElement(UIElement && move);

			UIElement &operator=(const UIElement &) = delete;
			UIElement &operator=(UIElement && move);


			// updates this UIElement and its children, if flagged invalid.
			void update();


			/// Label

			const Label &getLabel() const;
			/*Sets the text of the Label. Call @[updateLabel] to make changes visible.*/
			void setText(const u32string &text);
			const u32string &getText() const;

			/*Sets the font of the Label. Call @[updateLabel] to make changes visible.*/
			void setFont(const strong_handle<Font> &font);
			const strong_handle<Font> &getFont() const;

			// calls @[Label::update] and @[contentChanged].
			void updateLabel();


			/// Content





			/// Box Model

			// returns the border of the UiElement.
			const layout::Box<layout::Border> &getBorder() const;
			// invalidates the border model.
			void setBorder(const layout::Box<layout::Border> &border);

			const layout::Image &getBackground() const;
			// sets the background image and invalidates the background model.
			void setBackground(const layout::Image &background);

			// resolves the minimal width of this UIElement.
			float absoluteMinWidth() const;
			// resolves the minimal height of this UIElement.
			float absoluteMinHeight() const;
			// resolves the maximal width of this UIElement.
			float absoluteMaxWidth() const;
			// resolves the maximal height of this UIElement.
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

		};
	}
}


#endif