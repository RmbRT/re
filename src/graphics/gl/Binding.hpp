#ifndef __re_graphics_gl_binding_hpp_defined
#define __re_graphics_gl_binding_hpp_defined

#include "../../defines.hpp"
#include "Handle.hpp"

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			/** Represents a Binding slot for Handles. */
			class Binding
			{
				/** The currently bound Handle. */
				handle_t m_bound;
			public:
				/** Creates an empty Binding. */
				RECX Binding();
				/** Moves ownership of the given Binding. */
				REIL Binding(Binding &&);
				/** Moves ownership of the given Binding.
				@assert
					The left hand side argument must be empty.
				@assert
					Cannot move to self. */
				REIL Binding &operator=(Binding &&) &;
				/** @assert
					The Binding must be empty. */
				RE_DBG(REIL ~Binding();)

				/** Returns whether the given Handle is bound.
				@assert
					The given Handle must be valid.
				@param[in] handle:
					The Handle in question. */
				RECXDA bool bound(handle_t handle) const&;
				/** Returns whether there is a bound Handle. */
				RECXDA bool empty() const&;
				/** Binds the given Handle.
				@assert
					The given Handle must be valid.
				@param[in] handle:
					The Handle to be bound. */
				REIL void bind(handle_t handle) &;
				/** Unbinds the currently bound Handle.
				@assert
					There must be a currently bound Handle. */
				REIL void unbind() &;
				/** Called before destroying a Handle.
					If the Handle was bound, unbinds it.
				@assert
					The Handle must be valid.
				@param[in] handle:
					The Handle to bedestroyed. */
				REIL void on_invalidate(handle_t handle) &;
			};
		}
	}
}
#include "Binding.inl"

#endif