#include "TextNode.hpp"

namespace re
{
	namespace ui
	{
		TextNode::TextNode() : UINode(), label() { }
		TextNode::TextNode(const u32string &text, const strong_handle<Font> &font) : UINode(), label()
		{
			label.setText(text);
			setFont(font);
			label.setFont(font);
			label.update();
			updateBounds();
		}

		void TextNode::setText(u32string const& text)
		{
			label.setText(text);
			label.setFont(getFont());
			label.update();
			updateBounds();
		}
		const u32string &TextNode::getText() const
		{
			return label.getText();
		}

		void TextNode::updateBounds()
		{
			const math::fvec2 &sz = label.getSize();
			max_size = min_size = math::vec2<layout::Size>(layout::Absolute(sz.x), layout::Absolute(sz.y));
			contentChanged();
		}

		void TextNode::update()
		{
			const strong_handle<Font> &font = getFont();
			if(label.getFont() != font)
			{
				label.setFont(font);
				label.update();
			}

			UINode::update();
		}
	}
}