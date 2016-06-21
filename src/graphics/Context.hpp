#ifndef __re_graphics_context_hpp_defined
#define __re_graphics_context_hpp_defined

#include "../defines.hpp"
#include "../types.hpp"
#include "Version.hpp"
#include <Lock/Lock.hpp>
#include "Hints.hpp"

namespace re
{
	namespace graphics
	{
		class Window;
		/** Used to keep track of how many Windows are sharing a Context. */
		class ContextReferenceCounter
		{
		protected:
			REIL static void dereference(Context & context);
			REIL static void reference(Context & context);
			REIL static void make_current(Context & context);
		};

		/** Stores the GPU data of a Context. */
		class Context
		{	friend class ContextReferenceCounter;
			/** Points to the current Context of this thread. */
			thread_local static lock::ThreadSafe<Context *> s_current_context;
			/** If this Context is current, points to the pointer pointing to this Context. */
			lock::ThreadSafe<Context *> * m_current_thread;
			/** The API Version of this Context.
				This may not be equal to the requested Version. */
			Version m_version;

			/** How many Windows are sharing this Context. */
			uint_t m_references;

			/** The hints used to create this Context. */
			ContextHints m_hints;

			void make_current();
		public:
			/** Creates an invalid Context. */
			RECX Context(ContextHints const& hints, Version const& version);
			REIL Context(Context &&);
			REIL Context &operator=(Context &&);
			REIL virtual ~Context() = 0;

			/** Returns the version of the Context. */
			RECX Version const& version() const;
			/** Whether the Context is current in the active thread. */
			RECX bool current() const;
			/** Returns how many Windows reference this Context. */
			RECX uint_t references() const;

			RECX ContextHints const& hints() const;
		};
	}
}


#endif