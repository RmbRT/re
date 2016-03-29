namespace re
{
	namespace graphics
	{
		namespace GL
		{
			Buffer::Buffer(
				BufferType type,
				BufferAccess access,
				BufferUsage usage):
				Handle(),
				m_type(type),
				m_access(access),
				m_usage(usage)
			{
			}
		}
	}
}