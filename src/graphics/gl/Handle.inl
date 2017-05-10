namespace re
{
	namespace graphics
	{
		namespace gl
		{
			RECX Handle::Handle():
				m_handle(0)
			{
			}


			REIL Handle::Handle(Handle &&move):
				m_handle(move.m_handle)
			{
				move.m_handle = 0;
			}


			REIL Handle &Handle::operator=(Handle && move)
			{
				RE_DBG_ASSERT(&move != this && "Tried to move Handle to itself!");
				RE_DBG_ASSERT(!exists() && "Tried to overwrite existing Handle!");

				m_handle = move.m_handle;
				move.m_handle = 0;

				return *this;
			}


#ifdef RE_DEBUG
			Handle::~Handle()
			{
				RE_DBG_ASSERT(!exists() && "Handle was not properly cleaned up.");
			}
#endif

			REIL void Handle::set_handle(handle_t handle)
			{
				RE_DBG_ASSERT(!exists() && "Tried to overwrite existing Handle.");
				m_handle = handle;
			}

			REIL void Handle::null_handle()
			{
				RE_DBG_ASSERT(exists() && "Tried to reset nonexisting Handle.");
				m_handle = 0;
			}

			RECXDA bool Handle::exists() const
			{
				return m_handle != 0;
			}

			RECXDA handle_t Handle::handle() const
			{
				RE_DBG_ASSERT(exists() && "Tried to retrieve null handle.");
				return m_handle;
			}
		}
	}
}