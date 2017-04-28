#include "TextNode.hpp"

namespace re
{
	namespace ui
	{
		TextNode::TextNode(
			string32_t text,
			Shared<Font> font):
			UINode(),
			m_label()
		{
			m_label.set_text(text);
			UINode::set_font(font);
			m_label.set_font(font);
			m_label.update();
			update_bounds();
		}

		void TextNode::set_text(
			string32_t text)
		{
			m_label.set_text(std::move(text));
			m_label.set_font(UINode::font());
			m_label.update();
			update_bounds();
		}
		string32_t const& TextNode::text() const
		{
			return m_label.text();
		}

		void TextNode::update_bounds()
		{
			math::fvec2_t const& sz = m_label.size();
			UINode::set_width(layout::Absolute(sz.x));
			UINode::set_height(layout::Absolute(sz.y));
		}

		void TextNode::update()
		{
			Shared<Font> const& temp_font = UINode::font();
			if(m_label.font() != temp_font)
			{
				m_label.set_font(temp_font);
				m_label.update();
			}

			UINode::update();
		}
	}
}