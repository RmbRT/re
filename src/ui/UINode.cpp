#include "UINode.hpp"


namespace re
{
	namespace ui
	{
		void UINode::content_changed() const
		{
			const UINode * node = this;

			while(node)
			{
				node->m_invalid_width = true;
				node->m_invalid_height = true;
				node->m_invalid_children = true;

				node = node->m_parent;
			}
		}

		void UINode::update_models() const
		{
			m_borders.update_model();
			m_background.update_model();
		}


		UINode::UINode():
			m_parent(nullptr),
			m_invalid_width(true),
			m_invalid_height(true),
			m_temp_last_absolute_content_height(0),
			m_temp_last_absolute_content_width(0),
			m_invalid_children(true),
			m_font(nullptr),
			m_prev_sibling(nullptr),
			m_next_sibling(nullptr),
			m_background(graphics::gl::BufferAccess::Static)

		{ }

		UINode::UINode(UINode && move):
			m_parent(move.m_parent),
			m_prev_sibling(move.m_prev_sibling),
			m_next_sibling(move.m_next_sibling),
			m_children(std::move(move.m_children)),
			m_name(std::move(move.m_name)),
			m_font(std::move(move.m_font)),
			m_align(move.m_align),
			m_position(move.m_position),
			m_min_size(move.m_min_size),
			m_max_size(move.m_max_size),
			m_margin(move.m_margin),
			m_padding(move.m_padding),
			m_borders(std::move(move.m_borders)),
			m_background(std::move(move.m_background)),
			m_display(move.m_display),
			m_scrollbars(std::move(move.m_scrollbars)),
			m_invalid_children(move.m_invalid_children),
			m_temp_last_absolute_content_width(move.m_temp_last_absolute_content_width),
			m_temp_last_absolute_content_height(move.m_temp_last_absolute_content_height),
			m_invalid_width(move.m_invalid_width),
			m_invalid_height(move.m_invalid_height)

		{
			for(auto const& child : m_children)
				child->m_parent = this;
		}

		UINode &UINode::operator=(UINode &&move)
		{
			if(this == &move)
				return *this;

			m_parent = move.m_parent;
			m_prev_sibling = move.m_prev_sibling;
			m_next_sibling = move.m_next_sibling;
			m_children = std::move(move.m_children);
			m_name = std::move(move.m_name);
			m_font = std::move(move.m_font);
			m_align = move.m_align;
			m_position = move.m_position;
			m_min_size = move.m_min_size;
			m_max_size = move.m_max_size;
			m_margin = move.m_margin;
			m_padding = move.m_padding;
			m_borders = std::move(move.m_borders);
			m_background = std::move(move.m_background);
			m_display = move.m_display;
			m_scrollbars = std::move(move.m_scrollbars);
			m_invalid_children = move.m_invalid_children;
			m_temp_last_absolute_content_width = move.m_temp_last_absolute_content_width;
			m_temp_last_absolute_content_height = move.m_temp_last_absolute_content_height;
			m_invalid_width = move.m_invalid_width;
			m_invalid_height = move.m_invalid_height;

			for(auto const& child : m_children)
				child->m_parent = this;

			return *this;
		}


		void UINode::update()
		{
			update_models();

			for(auto const& child: m_children)
				child->update();
		}

		void UINode::draw(graphics::RenderSession &session) const
		{
			m_borders.draw();
			m_background.draw();

			for(auto const& child: m_children)
				child->draw(session);
		}

		void UINode::set_font(Shared<Font> font)
		{
			m_font = std::move(font);
		}
		Shared<Font> const& UINode::font() const
		{
			for(UINode const * node = this; node->m_parent != nullptr; node = node->m_parent)
				if(node->m_font)
					return node->m_font;

			// must not return nullptr here, because a reference is required.
			return m_font; // == nullptr
		}


		inline bool imply(bool a, bool implication) { return a? a&&implication : true; }

#define IMPLEMENT_SIZE_GETTER(name,parentGetter) \
			RE_ASSERT(imply(name.relative != 0, m_parent != nullptr));	\
			return name.relative ?	\
				name.absolute + name.relative * m_parent->parentGetter() :	\
				name.absolute;

#define WIDTH_DEPEND absolute_content_area_width
#define HEIGHT_DEPEND absolute_content_area_height


		float UINode::absolute_min_width() const
		{ IMPLEMENT_SIZE_GETTER(m_min_size.x, WIDTH_DEPEND) }

		float UINode::absolute_min_height() const
		{ IMPLEMENT_SIZE_GETTER(m_min_size.y, HEIGHT_DEPEND) }

		float UINode::absolute_max_width() const
		{ IMPLEMENT_SIZE_GETTER(m_max_size.x, WIDTH_DEPEND) }

		float UINode::absolute_max_height() const
		{ IMPLEMENT_SIZE_GETTER(m_max_size.y, HEIGHT_DEPEND) }

		float UINode::absolute_content_width() const
		{
			if(m_invalid_width)
			{
				m_invalid_width = false;
				float w = 0;

				for(auto const& child: m_children)
					w = math::max(w, child->absolute_box_width());
				m_temp_last_absolute_content_width = w;
			}
			return m_temp_last_absolute_content_width;
		}

		float UINode::absolute_content_height() const
		{
			if(m_invalid_height)
			{
				m_invalid_height = false;
				float h = 0;

				for(auto const& child: m_children)
					h = math::max(h, child->absolute_box_height());
				m_temp_last_absolute_content_height = h;
			}
			return m_temp_last_absolute_content_height;
		}


		float UINode::absolute_content_area_width() const
		{
			return math::cap(
				absolute_content_width(),
				absolute_min_width(),
				absolute_max_width());
		}

		float UINode::absolute_content_area_height() const
		{
			return math::cap(
				absolute_content_height(),
				absolute_min_height(),
				absolute_max_height());
		}


		float UINode::content_area_display_width() const
		{
			return (visible_scroll_bar_v() && m_scrollbars.y.obstructVision) ?
				absolute_content_area_width() - m_scrollbars.y.width :
				absolute_content_area_width();
		}

		float UINode::content_area_display_height() const
		{
			return (visible_scroll_bar_h() && m_scrollbars.x.obstructVision) ?
				absolute_content_area_height() - m_scrollbars.x.width :
				absolute_content_area_height();
		}



		bool UINode::visible_scroll_bar_h() const
		{
			switch(m_scrollbars.x.visibility)
			{
			case layout::ScrollBarVisibility::Always:
				return true;
			case layout::ScrollBarVisibility::Never:
				return false;
			case layout::ScrollBarVisibility::WhenOverflow:
				return absolute_content_width() > absolute_max_width();
			case layout::ScrollBarVisibility::WhenScrolling:
				return m_scrollbars.x.scrolling != 0;
			default:
				RE_ASSERTION_FAILURE("Invalid / unimplemented enum!");
			}
		}

		bool UINode::visible_scroll_bar_v() const
		{
			switch(m_scrollbars.y.visibility)
			{
			case layout::ScrollBarVisibility::Always:
				return true;
			case layout::ScrollBarVisibility::Never:
				return false;
			case layout::ScrollBarVisibility::WhenOverflow:
				return absolute_content_height() > absolute_max_height();
			case layout::ScrollBarVisibility::WhenScrolling:
				return m_scrollbars.y.scrolling != 0;
			default:
				RE_ASSERTION_FAILURE("Invalid / unimplemented enum!");
			}
		}

		float UINode::absolute_left() const
		{ IMPLEMENT_SIZE_GETTER(m_position.x, WIDTH_DEPEND) }

		float UINode::absolute_top() const
		{ IMPLEMENT_SIZE_GETTER(m_position.y, HEIGHT_DEPEND) }

		float UINode::absolute_margin_left() const
		{ IMPLEMENT_SIZE_GETTER(m_margin.left, WIDTH_DEPEND) }

		float UINode::absolute_margin_top() const
		{ IMPLEMENT_SIZE_GETTER(m_margin.top, HEIGHT_DEPEND) }

		float UINode::absolute_margin_right() const
		{ IMPLEMENT_SIZE_GETTER(m_margin.right, WIDTH_DEPEND) }

		float UINode::absolute_margin_bottom() const
		{ IMPLEMENT_SIZE_GETTER(m_margin.bottom, HEIGHT_DEPEND) }

		float UINode::absolute_padding_left() const
		{ IMPLEMENT_SIZE_GETTER(m_padding.left, WIDTH_DEPEND) }

		float UINode::absolute_padding_top() const
		{ IMPLEMENT_SIZE_GETTER(m_padding.top, HEIGHT_DEPEND) }

		float UINode::absolute_padding_right() const
		{ IMPLEMENT_SIZE_GETTER(m_padding.right, WIDTH_DEPEND) }

		float UINode::absolute_padding_bottom() const
		{ IMPLEMENT_SIZE_GETTER(m_padding.bottom, HEIGHT_DEPEND) }

		float UINode::absolute_box_width() const
		{
			return
				absolute_margin_left()
					+ m_borders.left_width()
						+ absolute_padding_left()
							+ absolute_content_area_width()
						+ absolute_padding_right()
					+ m_borders.right_width();
				+ absolute_margin_right();
		}

		float UINode::absolute_box_height() const
		{
			return
				absolute_margin_top()
					+ m_borders.top_width()
						+ absolute_padding_top()
							+ absolute_content_area_height()
						+ absolute_padding_bottom()
					+ m_borders.bottom_width()
				+ absolute_margin_bottom();
		}

		math::fvec2_t UINode::absolute_position() const
		{
			math::fvec2_t pos;
			const UINode * node = this;

			while(node)
			{
				pos.x += node->absolute_left() + node->absolute_box_width();
				pos.y += node->absolute_top() + node->absolute_box_height();
				node = node->m_prev_sibling;
			}
			return pos;
		}

		void UINode::set_min_width(layout::Size const& min_w)
		{
			m_min_size.x = min_w;
			content_changed();
		}

		void UINode::set_min_height(layout::Size const& min_h)
		{
			m_min_size.y = min_h;
			content_changed();
		}

		void UINode::set_max_width(layout::Size const& max_w)
		{
			m_max_size.x = max_w;
			content_changed();
		}
		void UINode::set_max_height(layout::Size const& max_h)
		{
			m_max_size.y = max_h;
			content_changed();
		}

		void UINode::set_width(layout::Size const& width)
		{
			m_min_size.x = m_max_size.x = width;
			content_changed();
		}
		void UINode::set_height(layout::Size const& height)
		{
			m_min_size.y = m_max_size.y = height;
			content_changed();
		}

		void UINode::set_margin(layout::Box<layout::Size> const& margin)
		{
			m_margin = margin;
			content_changed();
		}

		void UINode::set_margin_left(layout::Size const& margin)
		{
			m_margin.left = margin;
			content_changed();
		}
		void UINode::set_margin_top(layout::Size const& margin)
		{
			m_margin.top = margin;
			content_changed();
		}
		void UINode::set_margin_right(layout::Size const& margin)
		{
			m_margin.right = margin;
			content_changed();
		}
		void UINode::set_margin_bottom(layout::Size const& margin)
		{
			m_margin.bottom = margin;
			content_changed();
		}

		void UINode::set_padding(layout::Box<layout::Size> const& padding)
		{
			m_padding = padding;
			content_changed();
		}

		void UINode::set_padding_left(layout::Size const& padding)
		{
			m_padding.left = padding;
			content_changed();
		}
		void UINode::set_padding_top(layout::Size const& padding)
		{
			m_padding.top = padding;
			content_changed();
		}
		void UINode::set_padding_right(layout::Size const& padding)
		{
			m_padding.right = padding;
			content_changed();
		}
		void UINode::set_padding_bottom(layout::Size const& padding)
		{
			m_padding.bottom = padding;
			content_changed();
		}

		void UINode::set_left(layout::Size const& left)
		{
			m_position.x = left;
			content_changed();
		}
		void UINode::set_top(layout::Size const& top)
		{
			m_position.y = top;
			content_changed();
		}

		std::vector<Auto<UINode>> const& UINode::children() const
		{
			return m_children;
		}

		void UINode::add_child(
			Auto<UINode> node)
		{
			RE_ASSERT(node);
			RE_ASSERT(node->m_parent == nullptr);

			if(!m_children.empty())
			{
				m_children.back()->m_next_sibling = node.operator->();
				node->m_prev_sibling = m_children.back().operator->();
			}
			else
				node->m_prev_sibling = nullptr;

			node->m_next_sibling = nullptr;
			node->m_parent = this;

			m_children.push_back(std::move(node));
			content_changed();
		}


	}
}