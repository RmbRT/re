#ifndef __re_ui_textnode_hpp_defined
#define __re_ui_textnode_hpp_defined

#include "UINode.hpp"

namespace re
{
	namespace ui
	{
		class TextNode : public UINode
		{
			Label label;

			void updateBounds();
		public:
			TextNode();
			TextNode(const u32string &text);
			TextNode(const u32string &text, const strong_handle<Font> &font);
			
			void setText(const u32string &text);
			const u32string &getText() const;

			void update() override;

		};
	}
}

#endif