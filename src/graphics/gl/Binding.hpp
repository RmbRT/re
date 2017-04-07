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
			/** Represents a binding slot for handles. */
			class Binding
			{
				/** The currently bound handle. */
				handle_t m_bound;
			public:
				/** Creates an empty binding. */
				RECX Binding();
				/** Moves ownership of the given binding.
				@param[in] rhs:
					The binding to move from. */
				REIL Binding(
					Binding && rhs);
				/** Moves ownership of the given binding.
				@assert
					The left hand side argument must be empty.
				@assert
					Cannot move to self.
				@param[in] rhs:
					The binding to move from. */
				REIL Binding &operator=(
					Binding && rhs) &;
				/** @assert
					The Binding must be empty. */
				RE_DBG(RECXDA) ~Binding() RE_RLS(= default);
				/** Returns whether the given handle is bound.
				@assert
					The given handle must be valid.
				@param[in] handle:
					The handle in question. */
				RECXDA bool bound(
					handle_t handle) const&;
				/** Returns whether there is a bound handle. */
				RECXDA bool empty() const&;
				/** Binds the given handle.
				@assert
					The given handle must be valid.
				@param[in] handle:
					The handle to be bound. */
				REIL void bind(handle_t handle) &;
				/** Unbinds the currently bound handle.
				@assert
					There must be a currently bound handle. */
				REIL void unbind() &;
				/** Called before destroying a handle.
					If the handle was bound, unbinds it.
				@assert
					The handle must be valid.
				@param[in] handle:
					The handle to be destroyed. */
				REIL void on_invalidate(handle_t handle) &;
			};
		}
	}
}

#include "Binding.inl"

#endif