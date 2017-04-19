#include "Context.hpp"
#include "OpenGL.hpp"
#include "../Window.hpp"

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			thread_local lock::ThreadSafe<Context *> Context::s_current_context(nullptr);

			void Context::make_current()
			{
				if(current())
					return;

				lock::WriteLock<Context *> w_current_context(s_current_context);

				if(*w_current_context)
					(*w_current_context)->on_deselect();

				*w_current_context = this;
				m_current_thread = &s_current_context;

				on_select();
			}

			void Context::make_none_current()
			{
				lock::WriteLock<Context *> w_current_context(s_current_context);

				if(*w_current_context)
				{
					(*w_current_context)->on_deselect();
					(*w_current_context) = nullptr;
				}

				glfwMakeContextCurrent(nullptr);
			}

			ContextHints::ContextHints():
				version(0,0),
				profile(OpenGLProfile::Any)
			{
			}
		}
	}
}