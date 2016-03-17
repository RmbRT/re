namespace re
{
	namespace graphics
	{
		namespace GL
		{
			RenderBuffer::~RenderBuffer()
			{
				RE_DBG_ASSERT(!exists() && "Render buffer was not properly cleaned up!");
			}

			uint32 RenderBuffer::width() const
			{
				return m_width;
			}

			uint32 RenderBuffer::height() const
			{
				return m_height;
			}
		}
	}
}