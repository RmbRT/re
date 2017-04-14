#ifndef __re_ui_uielement2_hpp_defined
#define __re_ui_uielement2_hpp_defined

#include "../types.hpp"
#include "../math/Vector.hpp"
#include "../graphics/gl/Texture.hpp"
#include "Rendering.hpp"
#include "Label.hpp"
#include "layout/Layout.hpp"
#include "../graphics/RenderSession.hpp"

namespace re
{
	namespace ui
	{
		/** The base class for all UI elements.
		Contains a Box Model representation, similar to the one found in HTML / CSS.
		Contains a list of UINodes as children.
		@usage:
			Deriving classes should override the method `update_models()` to create a custom look. */
		class UINode
		{
		protected:
			/** The parent UINode, if any. */
			UINode * m_parent;

			/** The previous sibling within the same parent node. */
			UINode * m_prev_sibling;
			/** The next sibling within the same parent node. */
			UINode * m_next_sibling;

			/** This node's children. */
			std::vector<Auto<UINode>> m_children;

			/** This node's internal name. */
			string8_t m_name;

			/** This node's default font.
				This is used for inheriting fonts from parent nodes. */
			Shared<Font> m_font;

			/** This node's alignment. */
			math::Vec2<layout::Align> m_align;

			/** The node's position. */
			math::Vec2<layout::Size> m_position;
			/** The node's minimum size. */
			math::Vec2<layout::Size> m_min_size;
			/** The node's maximum size. */
			math::Vec2<layout::Size> m_max_size;

			/** The node's margin around its edges. */
			layout::Box<layout::Size> m_margin;
			/** The node's padding within its edges. */
			layout::Box<layout::Size> m_padding;
			/** The node's border. */
			layout::Box<layout::Border> m_border;

			/** The border's corner images. */
			layout::Image m_border_corner_top_left,
				m_border_corner_top_right,
				m_border_corner_bottom_left,
				m_border_corner_bottom_right;

			/** The border's corner models. */
			VertexArray
				m_border_corner_top_left_model,
				m_border_corner_top_right_model,
				m_border_corner_bottom_left_model,
				m_border_corner_bottom_right_model;

			/** The node's background image. */
			layout::Image m_background;

			/** The node's display behaviour. */
			layout::Display m_display;

			/** The node's scrollbars. */
			math::Vec2<layout::ScrollBar> m_scrollbars;

			/** The node's background model. */
			mutable Auto<VertexArray> m_background_model;
			/** The node's border model. */
			mutable Auto<VertexArray> m_border_model;
			/** The node's border cornel model.*/
			mutable Auto<VertexArray> m_border_corner_model;

			/** Whether the background model is invalid. */
			mutable bool m_invalid_background_model;
			/** Whether the border model is invalid. */
			mutable bool m_invalid_border_model;
			/** Whether the children are invalid. */
			mutable bool m_invalid_children;

			/** invalidates the calculated width and height, and the border and background models, and the children. */
			void content_changed() const;

			/** Called by `update()`.
				Override this to create custom models. */
			virtual void update_models() const;
			/** Called by `update_models()`.
				Override this to create custom border models. */
			virtual void update_border_model() const;
			/** Called by `update_models()`.
				Override this to create custom background models. */
			virtual void update_background_model() const;
		private:
			/** Used to prevent an infinite recursion when resolving percentage based size values. */
			mutable float m_temp_last_absolute_content_width;
			/** Used to prevent an infinite recursion when resolving percentage based size values. */
			mutable float m_temp_last_absolute_content_height;
			/** Indicates that the size values should be updated. */
			mutable bool m_invalid_width;
			/** Indicates that the size values should be updated. */
			mutable bool m_invalid_height;
		public:
			UINode();
			UINode(const UINode &) = delete;
			UINode(UINode && move);

			virtual ~UINode() {}

			UINode &operator=(const UINode &) = delete;
			UINode &operator=(UINode && move);

			/** Updates contents of the children and this node. */
			virtual void update();
			/** Draws the node.
			@param[in, out] session:
				The render session to use for drawing this node. */
			virtual void draw(
				graphics::RenderSession &session) const;

			/// Content

			/** Sets this node's font.
			@param[in] font:
				This node's font, or null. */
			void set_font(
				Shared<Font> font);
			/** Retrieves this node's font setting.
				Use `inherited_font()` to also check for ancestors using a font.
			@return
				Null, if no font is set for this node, otherwise, this node's font. */
			Shared<Font> const& font() const;
			/** Retrieves the font inherited by the closest ancestor, or self.
				Finds the closest ancestor that has a font set, and returns its font.
			@return
				The font that is set for this node, or null, if no font was set. */
			Shared<Font> inherited_font() const;

			/** @retunr This node's children. */
			std::vector<Auto<UINode>> const& children() const;

			/** Adds a node as a child.
			@param[in] node:
				The node to add.
				Must not be a child of any other UINode already. */
			void add_child(
				Auto<UINode> node);

			/** Finds a child by name.
			@return the child with the requested name, or null. */
			UINode * find_child(
				char const * name) const;

			/// Box Model

			/** Returns the border of the UINode. */
			layout::Box<layout::Border> const& border() const;
			/** Sets the border and invalidates the border model. */
			void set_border(
				layout::Box<layout::Border> const& border);

			/** Returns the background image. */
			layout::Image const& background() const;
			/** sets the background image and invalidates the background model. */
			void set_background(
				layout::Image const& background);

			/** resolves the minimal width of this UINode. */
			float absolute_min_width() const;
			/** resolves the minimal height of this UINode. */
			float absolute_min_height() const;
			/** resolves the maximal width of this UINode. */
			float absolute_max_width() const;
			/** resolves the maximal height of this UINode. */
			float absolute_max_height() const;

			/** the width of the area containing all children. unaffected by min / max width. */
			float absolute_content_width() const;
			/** the height of the area containing all children. unaffected by min / max height. */
			float absolute_content_height() const;

			/** the width of the content area. affected by min / max width. */
			float absolute_content_area_width() const;
			/** the height of the content area. affected by min / max height. */
			float absolute_content_area_height() const;

			/** the width of the content area, reduced by the width of the vertical scroll bars. */
			float content_area_display_width() const;
			/** the height of the content area, reduced by the width of the horizontal scroll bars. */
			float content_area_display_height() const;

			/** checks whether the horizontal scroll bar is visible. */
			bool visible_scroll_bar_h() const;
			/** checks whether the vertical scroll bar is visible. */
			bool visible_scroll_bar_v() const;

			/** resolves the offset on the horizontal axis. */
			float absolute_left() const;
			/** resolves the offset on the vertical axis. */
			float absolute_top() const;

			/** resolves the left margin. */
			float absolute_margin_left() const;
			/** resolves the top margin. */
			float absolute_margin_top() const;
			/** resolves the right margin. */
			float absolute_margin_right() const;
			/** resolves the bottom margin. */
			float absolute_margin_bottom() const;

			/** resolves the left padding. */
			float absolute_padding_left() const;
			/** resolves the top padding. */
			float absolute_padding_top() const;
			/** resolves the right padding. */
			float absolute_padding_right() const;
			/** resolves the bottom padding. */
			float absolute_padding_bottom() const;

			/** Resolves the width of the whole box.
			This contains the border, margin, padding, and content area. */
			float absolute_box_width() const;
			/** Resolves the height of the whole box.
			This contains the border, margin, padding, and content area. */
			float absolute_box_height() const;

			/** calculates the position of this UINode relative to its parents origin. */
			math::fvec2_t absolute_position() const;

			void set_min_width(
				layout::Size const& min_w);
			void set_min_height(
				layout::Size const& min_h);
			void set_max_width(
				layout::Size const& max_w);
			void set_max_height(
				layout::Size const& max_h);
			/** sets both min and max width to `width`. */
			void set_width(
				layout::Size const& width);
			/** sets both min and max height to `height`. */
			void set_height(
				layout::Size const& height);

			void setMargin(
				layout::Box<layout::Size> const& margin);
			void setMargin_left(
				layout::Size const& margin);
			void setMargin_right(
				layout::Size const& margin);
			void setMargin_top(
				layout::Size const& margin);
			void setMargin_bottom(
				layout::Size const& margin);

			void set_padding(
				layout::Box<layout::Size> const& padding);
			void set_padding_left(
				layout::Size const& padding);
			void set_padding_top(
				layout::Size const& padding);
			void set_padding_right(
				layout::Size const& padding);
			void set_padding_bottom(
				layout::Size const& padding);

			void set_border_left(
				layout::Border const& border);
			void set_border_top(
				layout::Border const& border);
			void set_border_right(
				layout::Border const& border);
			void set_border_bottom(
				layout::Border const& border);

			void set_border_top_left_corner(
				layout::Image const& corner);
			void set_border_top_right_corner(
				layout::Image const& corner);
			void set_border_bottom_left_corner(
				layout::Image const& corner);
			void set_border_bottom_right_corner(
				layout::Image const& corner);

			void set_left(
				layout::Size const& left);
			void set_top(
				layout::Size const& top);
		};
	}
}


#endif