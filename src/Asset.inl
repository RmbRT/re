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

	Utf8String const& AssetBase::getName() const
	{
		return name;
	}

	REIL void AssetBase::setName(Utf8String name)
	{
		this->name = std::move(name);
	}

	REIL bool AssetBase::hasName() const
	{
		return !name.empty();
	}
}