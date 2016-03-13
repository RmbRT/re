namespace re
{
	namespace graphics
	{
		namespace GL
		{
			GLHandle::GLHandle():
				m_gl_handle(0)
			{
			}

			
			GLHandle::GLHandle(GLHandle &&move):
				m_gl_handle(move.m_gl_handle)
			{
				move.m_gl_handle = 0;
			}

			
			GLHandle &GLHandle::operator=(GLHandle && move)
			{
				RE_DBG_ASSERT(!exists() && "Tried to overwrite existing GLHandle!");
				
				if(&move != this)
				{
					m_gl_handle = move.m_gl_handle;
					move.m_gl_handle = 0;
				}

				return *this;
			}

			
			GLHandle::~GLHandle()
			{
				RE_DBG_ASSERT(!exists() && "GLHandle was not properly cleaned up.");
			}

			
			bool GLHandle::exists() const
			{
				return m_gl_handle != 0;
			}

			void GLHandle::set_gl_handle(gl_handle_t gl_handle)
			{
				RE_DBG_ASSERT(!exists() && "Tried to overwrite existing GLHandle.");
				m_gl_handle = gl_handle;
			}

			void GLHandle::null_gl_handle()
			{
				m_gl_handle = 0;
			}
		}
	}
}