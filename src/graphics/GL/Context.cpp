#include "Context.hpp"
#include "OpenGL.hpp"
#include "../Window.hpp"

namespace re
{
	namespace graphics
	{
		namespace GL
		{
			void Context::make_current()
			{
				if(current())
					return;

				lock::WriteLock<Context *> w_current_context(tlsm_current);

				glfwMakeContextCurrent(m_context);

				if(*w_current_context)
					(*w_current_context)->on_deselect();

				*w_current_context = (Window *) this;
				m_current = *w_current_context;
			}

			void Context::make_none_current()
			{
				lock::WriteLock<Context *> w_current_context(tlsm_current);

				if(*w_current_context)
				{
					(*w_current_context)->on_deselect();
					(*w_current_context) = nullptr;
				}

				glfwMakeContextCurrent(nullptr);
			}
		}
	}
}