namespace re
{
	namespace graphics
	{
		namespace gl
		{
			Binding::Binding():
				m_bound(0)
			{
			}
			
			Binding::Binding(Binding && move):
				m_bound(move.m_bound)
			{
				move.m_bound = 0;
			}

			Binding::operator=(Binding && move) &
			{
				RE_DBG_ASSERT(&move != this);
				RE_DBG_ASSERT(empty());

				m_bound = move.m_bound;
				move.m_bound = 0;
			}

			Binding::~Binding()
			{
				RE_DBG_ASSERT(!m_bound && "Did not properly unbind item.");
			}

			bool Binding::bound(handle_t handle) const&
			{
				RE_DBG_ASSERT(handle != 0);
				return m_bound == handle;
			}

			bool Binding::empty() const&
			{
				return !m_bound;
			}

			void Binding::bind(handle_t handle) &
			{
				RE_DBG_ASSERT(handle != 0);
				m_bound = handle;
			}

			void Binding::unbind() &
			{
				RE_DBG_ASSERT(!empty());
				m_bound = 0;
			}

			void Binding::on_invalidate(handle_t handle) &
			{
				RE_DBG_ASSERT(handle != 0);

				if(!empty() && bound(handle))
					unbind();
			}
		}
	}
}