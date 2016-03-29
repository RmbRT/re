namespace re
{
	namespace graphics
	{
		namespace GL
		{
			Context::Context():
				m_version(0,0),
				m_context(nullptr)
			{
			}

			Context(Context && move):
				m_version(move.m_version),
				m_context(move.m_context)
			{
				if(move.current())
					tlsm_current = this;

				move.m_version = Version(0,0);
				move.m_context = nullptr;
			}

			Context &operator=(Context && move)
			{
				RE_DBG_ASSERT(this != &move);
				RE_DBG_ASSERT(!valid());

				m_version = move.m_version;
				move.m_version = Version(0,0);
				m_current = move.m_current;
				move.m_current = nullptr;

				if(current())
				*m_current->writeLock() = this;

				return *this;
			}

			Context::~Context()
			{
				remove_if_current();
			}

			void Context::remove_if_current()
			{
				if(current())
					tlsm_current.writeLock() = nullptr;
				current = nullptr;
			}

			void Context::on_deselect()
			{
				RE_DBG_ASSERT(current());
				m_current = nullptr;
			}

			Version const& Context::version() const
			{
				return m_version;
			}

			void Context::version(Version const& acquired_version)
			{
				RE_DBG_ASSERT(!valid() && "Context had a valid version already!");

				m_version = acquired_version;
			}

			bool Context::current() const
			{
				return m_current;
			}

			bool Context::valid() const
			{
				return m_version.valid();
			}
		}
	}
}