namespace re
{
	namespace file
	{
		namespace IniFile
		{
			string const& Entry::content() const
			{
				return m_content;
			}

			string const& Entry::key() const
			{
				return m_key;
			}

			string const& Entry::comment() const
			{
				return m_comment;
			}

			string & Entry::comment()
			{
				return m_comment;
			}

			Entry * Section::operator[](string const& name)
			{
				return find_entry(name);
			}

			Entry const* Section::operator[](string const& name) const
			{
				return find_entry(name);
			}

			Section * IniFile::operator[](string const& name)
			{
				return find_entry(name);
			}

			Section const* IniFile::operator[](string const& name)
			{
				return find_entry(name);
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