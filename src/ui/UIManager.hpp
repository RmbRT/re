#ifndef __re_ui_uimanager_hpp_defined
#define __re_ui_uimanager_hpp_defined

#include "UIElement.hpp"
#include "../types.hpp"
#include "../input/InputManager.hpp"
#include "../math/Vector.hpp"

namespace re
{
	namespace ui
	{
		class UIManager
		{
			notnull<UIElement> root;
			math::fvec2 cursor;
			unsafe<input::InputManager> inputManager;
		public:

			/*Updates the mouse position and checks for and generates events
			for the <root> UIElement and its children.*/
			void update(const math::fvec2 &new_cursor, float delta_time);

		};

	}
}



#endif