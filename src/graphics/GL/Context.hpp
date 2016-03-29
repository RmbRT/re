#ifndef __re_graphics_gl_context_hpp_defined
#define __re_graphics_gl_context_hpp_defined

#include "../../defines.hpp"
#include "../../types.hpp"
#include "Version.hpp"
#include <Lock/Lock.hpp>

namespace re
{
	namespace graphics
	{
		namespace GL
		{
			class Context
			{
				/** Points to the current Context of this thread. */
				thread_local static lock::ThreadSafe<Context *> tlsm_current;
				/** If this Context is current, points to the pointer pointing to this Context. */
				lock::ThreadSafe<Context *> * m_current;

				Version m_version;
				GLFWwindow * m_context;

				REINL void remove_if_current();
				REINL void on_deselect();
			public:
				/** Creates an invalid Context. */
				RECX Context();

				REINL Context(Context &&);
				REINL Context &operator=(Context &&);

				REINL virtual ~Context() = 0;

				/** Returns the version of the Context. */
				RECX Version const& version() const;
				/** Used after a context was successfully created, to set the version of the acquired */
				REINL void version(Version const& acquired_version);

				RECX bool current() const;
				RECX bool valid() const;
				void make_current();

				static void make_none_current();
			};
		}
	}
}


#endif