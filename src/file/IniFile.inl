namespace re
{
	namespace file
	{
		namespace IniFile
		{
			EntryValue Entry::value_type() const
			{
				return m_value_type;
			}

			string8_t const& Entry::content() const
			{
				return m_content;
			}

			string8_t const& Entry::key() const
			{
				return m_key;
			}

			string8_t const& Entry::comment() const
			{
				return m_comment;
			}

			Entry * Section::operator[](char const * name)
			{
				return find_entry(name);
			}

			Entry const * Section::operator[](char const * name) const
			{
				return find_entry(name);
			}

			Section * IniFile::operator[](char const * name)
			{
				return find_section(name);
			}

			Section const * IniFile::operator[](char const * name) const
			{
				return find_section(name);
			}

			Section & IniFile::unnamed_section()
			{
				return m_unnamed_section;
			}

			Section const& IniFile::unnamed_section() const
			{
				return m_unnamed_section;
			}
		}
	}
}