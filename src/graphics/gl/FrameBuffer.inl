namespace re
{
	namespace graphics
	{
		namespace gl
		{
			bool FrameBuffer::has_color() const
			{
				RE_DBG_ASSERT(exists());
				return m_color.exists();
			}

			bool FrameBuffer::has_depth() const
			{
				RE_DBG_ASSERT(exists());
				return m_depth.exists();
			}
			bool FrameBuffer::has_stencil() const
			{
				RE_DBG_ASSERT(exists());
				return m_stencil.exists();
			}
			bool FrameBuffer::has_depth_stencil() const
			{
				RE_DBG_ASSERT(exists());
				return m_depth_stencil.exists();
			}
		}
	}
}