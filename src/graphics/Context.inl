namespace re
{
	namespace graphics
	{
		namespace gl
		{
			void ContextReferenceCounter::dereference(Context & context)
			{
				RE_DBG_ASSERT(context.m_references != 0);
				--context.m_references;
			}

			void ContextReferenceCounter::reference(Context & context)
			{
				context.m_references++;
			}

			void ContextReferenceCounter::make_current(Context & context)
			{
				context.make_current();
			}
			
			Context::Context(Version const& version):
				m_current_thread(nullptr),
				m_version(version),
				m_references(0)
			{
			}

			Context(Context && move):
				m_version(move.m_version),
				m_context(move.m_context),
				m_current_thread(move.m_current_thread),
				m_references(0)
			{
				RE_DBG_ASSERT(move.m_references == 0
					&& "Tried to move referenced Context.");

				if(move.current())
					tlsm_current = this;

				move.m_version = Version(0,0);
				move.m_current_thread = 0;
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
				if(valid())
				{
					if(current())
						*m_current = nullptr;
				}
			}

			Version const& Context::version() const
			{
				return m_version;
			}

			bool Context::current() const
			{
				return m_current;
			}

			uint_t Context::references() const
			{
				return m_references;
			}
		}
	}
}