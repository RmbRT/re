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

			REIL Context::Context(
				ContextHints const& hints,
				Version const& version):
				m_current_thread(nullptr),
				m_version(version),
				m_references(0),
				m_hints(hints)
			{
			}

			REIL Context::Context(Context && move):
				m_current_thread(move.m_current_thread),
				m_version(move.m_version),
				m_references(0),
				m_hints(std::move(move.m_hints))
			{
				RE_DBG_ASSERT(move.m_references == 0
					&& "Tried to move referenced Context.");

				if(move.current())
					*lock::write_lock(s_current_context) = this;

				move.m_version = Version(0,0);
				move.m_current_thread = nullptr;
			}

			Context &Context::operator=(Context && move)
			{
				RE_DBG_ASSERT(this != &move);
				RE_DBG_ASSERT(!valid());

				m_version = move.m_version;
				move.m_version = Version(0,0);
				m_current_thread = move.m_current_thread;
				move.m_current_thread = nullptr;

				if(current())
					*lock::write_lock(s_current_context) = this;

				return *this;
			}

			Context::~Context()
			{
				if(m_version.valid())
				{
					if(current())
						*lock::write_lock(*m_current_thread) = nullptr;
				}
			}

			Version const& Context::version() const
			{
				return m_version;
			}

			bool Context::current() const
			{
				return m_current_thread;
			}

			uint_t Context::references() const
			{
				return m_references;
			}

			bool Context::require_version(
				Version const& minimum)
			{
				auto lock = lock::read_lock(s_current_context);
				return *lock && (*lock)->version() >= minimum;
			}

			bool Context::require()
			{
				return *lock::read_lock(s_current_context);
			}
		}
	}
}