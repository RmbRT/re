namespace re
{
	namespace graphics
	{
		namespace gl
		{
			RECX Binding::Binding():
				m_bound(0)
			{
			}

			REIL Binding::Binding(Binding && move):
				m_bound(move.m_bound)
			{
				move.m_bound = 0;
			}

			REIL Binding &Binding::operator=(Binding && move) &
			{
				RE_DBG_ASSERT(&move != this);
				RE_DBG_ASSERT(empty());

				m_bound = move.m_bound;
				move.m_bound = 0;
			}

#ifdef RE_DEBUG
			REIL Binding::~Binding()
			{
				RE_DBG_ASSERT(!m_bound && "Did not properly unbind item.");
			}
#endif

			RECXDA bool Binding::bound(handle_t handle) const&
			{
				RE_DBG_ASSERT(handle != 0);
				return m_bound == handle;
			}

			RECXDA bool Binding::empty() const&
			{
				return !m_bound;
			}

			REIL void Binding::bind(handle_t handle) &
			{
				RE_DBG_ASSERT(handle != 0);
				m_bound = handle;
			}

			REIL void Binding::unbind() &
			{
				RE_DBG_ASSERT(!empty());
				m_bound = 0;
			}

			REIL void Binding::on_invalidate(handle_t handle) &
			{
				RE_DBG_ASSERT(handle != 0);

				if(bound(handle))
					unbind();
			}
		}
	}
}