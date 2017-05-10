namespace re
{
	REIL string8_t const& TextAsset::content() const
	{
		return m_content;
	}

	REIL void TextAsset::set_content(
		string8_t const& text)
	{
		m_content = text;
	}

}	