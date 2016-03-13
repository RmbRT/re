namespace re
{
	namespace graphics
	{
		namespace GL
		{
			GLBuffer::~GLBuffer()
			{
				RE_DBG_ASSERT(!exists() && "Did not properly release GLBuffer!");
			}
		}
	}
}