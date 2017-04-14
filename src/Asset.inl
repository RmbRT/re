namespace re
{
	RECX AssetBase::AssetBase():
		m_name()
	{
	}

	REIL AssetBase::AssetBase(string8_t name):
		m_name(std::move(name))
	{
	}

	string8_t const& AssetBase::name() const
	{
		return m_name;
	}
	string8_t & AssetBase::name()
	{
		return m_name;
	}

	REIL bool AssetBase::has_name() const
	{
		return !m_name.empty();
	}
}