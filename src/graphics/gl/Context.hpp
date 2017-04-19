#ifndef __re_graphics_gl_context_hpp_defined
#define __re_graphics_gl_context_hpp_defined

#include "../../defines.hpp"
#include "../../types.hpp"
#include "../../util/Maybe.hpp"
#include "Version.hpp"
#include <Lock/Lock.hpp>
#include <vector>

namespace re
{
	namespace graphics
	{
		class Window;
		namespace gl
		{
			enum class ClientAPI
			{
				OpenGL,
				OpenGLES
			};

			enum class OpenGLProfile
			{
				Core,
				Compat,
				Any
			};

			struct ContextHints
			{
				ContextHints();
				Version version;
				util::Maybe<ClientAPI> client_api;
				OpenGLProfile profile;
			};

			/** Stores the GPU data of a Context.
				This class should be derived from and the deriving class should store all GPU objects it uses, so that the data can be shared between multiple windows effectively. Note that this class does not have any behaviour at all, and `Window::make_context_current()` is the function that actually controls what context is set to current.  */
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

				/** Makes the context the current context. */
				void make_current();
			public:
				/** Creates a context object.
					This does not actually create anything on the GPU.
				@param[in] hints:
					The context creation hints.
				@param[in] version:
					The context version. */
				REIL Context(
					ContextHints const& hints,
					Version const& version);
				/** Moves a context. */
				REIL Context(Context &&);
				REIL Context &operator=(Context &&);
				REIL virtual ~Context() = 0;

				/** Returns the version of the Context. */
				REIL Version const& version() const;
				/** Whether the Context is current in the active thread. */
				REIL bool current() const;
				/** Returns how many Windows reference this Context. */
				REIL uint_t references() const;

				REIL ContextHints const& hints() const;

				static void make_none_current();

				/** Returns whether a context with a version >= the requested version is active. */
				REIL static bool require_version(
					Version const& minimum);
				/** Returns whether a context is active. */
				REIL static bool require();

				virtual void on_select() = 0;
				virtual void on_deselect() = 0;
			};

			/** Used to keep track of how many Windows are sharing a Context. */
			class ContextReferenceCounter
			{
			protected:
				REIL static void dereference(Context & context);
				REIL static void reference(Context & context);
				REIL static void make_current(Context & context);
			};
		}
	}
}

#include "Context.inl"

#endif