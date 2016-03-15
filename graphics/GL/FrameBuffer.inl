namespace re
{
	namespace graphics
	{
		namespace GL
		{
			FrameBuffer::FrameBuffer()
			{
				RE_DBG_ASSERT(!exists() &&
					"Frame buffer not properly cleaned up!");
				RE_DBG_ASSERT(!has_color() &&
					"Frame buffer color attachment not properly cleaned up!");
				RE_DBG_ASSERT(!has_depth() &&
					"Frame buffer depth attachment not properly cleaned up!");
				RE_DBG_ASSERT(!has_stencil() &&
					"Frame buffer stencil attachment not properly cleaned up!");
				RE_DBG_ASSERT(!has_depth_stencil() &&
					"Frame buffer depth stencil attachment not properly cleaned up!");
			}

			bool FrameBuffer::has_color() const
			{
				return m_color.exists();
			}

			bool FrameBuffer::has_depth() const
			{
				return m_depth.exists();
			}
			bool FrameBuffer::has_stencil() const
			{
				return m_stencil.exists();
			}
			bool FrameBuffer::has_depth_stencil() const
			{
				return m_depth_stencil.exists();
			}
		}
	}
}