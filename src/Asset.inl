namespace re
{
	RECX AssetBase::AssetBase():
		m_name()
	{
	}

	REIL AssetBase::AssetBase(Utf8String name):
		m_name(std::move(name))
	{
	}

	Utf8String const& AssetBase::name() const
	{
		return m_name;
	}
	Utf8String & AssetBase::name()
	{
		return m_name;
	}

	REIL bool AssetBase::has_name() const
	{
		return !m_name.empty();
	}
}