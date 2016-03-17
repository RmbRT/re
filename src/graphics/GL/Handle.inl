namespace re
{
	namespace graphics
	{
		namespace GL
		{
			Handle::Handle():
				m_handle(0)
			{
			}

			
			Handle::Handle(Handle &&move):
				m_handle(move.m_handle)
			{
				move.m_handle = 0;
			}

			
			Handle &Handle::operator=(Handle && move)
			{
				RE_DBG_ASSERT(!exists() && "Tried to overwrite existing Handle!");
				
				if(&move != this)
				{
					m_handle = move.m_handle;
					move.m_handle = 0;
				}

				return *this;
			}

			
			Handle::~Handle()
			{
				RE_DBG_ASSERT(!exists() && "Handle was not properly cleaned up.");
			}

			
			bool Handle::exists() const
			{
				return m_handle != 0;
			}

			void Handle::set_handle(handle_t handle)
			{
				RE_DBG_ASSERT(!exists() && "Tried to overwrite existing Handle.");
				m_handle = handle;
			}

			void Handle::null_handle()
			{
				m_handle = 0;
			}
		}
	}
}