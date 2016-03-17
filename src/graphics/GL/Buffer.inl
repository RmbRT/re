namespace re
{
	namespace graphics
	{
		namespace GL
		{
			Buffer::~Buffer()
			{
				RE_DBG_ASSERT(!exists() && "Did not properly release Buffer!");
			}
		}
	}
}