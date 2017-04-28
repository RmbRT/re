#ifndef __re_ui_textnode_hpp_defined
#define __re_ui_textnode_hpp_defined

#include "UINode.hpp"

namespace re
{
	namespace ui
	{
		class TextNode : public UINode
		{
			Label m_label;

			void update_bounds();
		public:
			TextNode() = default;
			TextNode(string32_t text);
			TextNode(string32_t text, Shared<Font> font);

			void set_text(
				string32_t text);
			string32_t const& text() const;

			void update() override;

		};
	}
}

#endif