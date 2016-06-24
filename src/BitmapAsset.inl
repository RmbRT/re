namespace re
{
	RECX BitmapAsset::BitmapAsset():
		m_content(),
		AssetBase()
	{
	}

	BitmapAsset::BitmapAsset(
		Utf8String name,
		graphics::Bitmap content):
		m_content(std::move(content)),
		AssetBase(std::move(name))
	{
	}

	BitmapAsset::BitmapAsset(
		graphics::Bitmap content):
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

	graphics::Bitmap const& BitmapAsset::bitmap() const
	{
		return m_content;
	}
	void BitmapAsset::set_bitmap(graphics::Bitmap bitmap)
	{
		m_content = std::move(bitmap);
	}
}