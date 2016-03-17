#ifndef __re_ui_button_hpp_defined
//#define __re_ui_button_hpp_defined

#include "../input/Input.hpp"
#include "UIElement.hpp"

namespace re
{
	namespace ui
	{
		class Button
		{
			~Button() = delete;
		public:
			static void onKey(UIElement &sender, const input::KeyEvent &event);
			static void onInput(UIElement &sender, uint32 codepoint);
			static void onCursorMove(UIElement &sender, const math::fvec2 &cursor);
			static void onCursorEnter(UIElement &sender);
			static void onCursorLeave(UIElement &sender);
		};

		unique_handle<UIElement> allocButton(const string &name);
		unique_handle<UIElement> allocButton(void);
	}
}

#endif