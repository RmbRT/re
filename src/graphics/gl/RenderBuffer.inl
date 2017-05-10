namespace re
{
	namespace graphics
	{
		namespace gl
		{
			uint32_t RenderBuffer::width() const
			{
				return m_width;
			}

			uint32_t RenderBuffer::height() const
			{
				return m_height;
			}

			REIL bool RenderBuffer::bound() const
			{
				RE_DBG_ASSERT(exists());
				return s_bound.bound(handle());
			}
		}
	}
}