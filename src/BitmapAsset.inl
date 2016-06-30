namespace re
{
	RECX BitmapAsset::BitmapAsset():
		m_content(),
		AssetBase()
	{
	}

	BitmapAsset::BitmapAsset(
		Utf8String name,
		graphics::Bitmap2D content):
		m_content(std::move(content)),
		AssetBase(std::move(name))
	{
	}

	BitmapAsset::BitmapAsset(
		graphics::Bitmap2D content):
		m_content(std::move(content)),
		AssetBase()
	{
	}

	BitmapAsset::BitmapAsset(
		Utf8String name):
		m_content(),
		AssetBase(std::move(name))
	{
	}

	graphics::Bitmap2D const& BitmapAsset::bitmap() const
	{
		return m_content;
	}
	graphics::Bitmap2D &BitmapAsset::bitmap()
	{
		return m_content;
	}
}