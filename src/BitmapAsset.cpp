#include "BitmapAsset.hpp"
#include "LogFile.hpp"
#include "util/Error.hpp"

namespace re
{
	bool BitmapAsset::load_from_file(std::ifstream &file)
	{
		if(!file.is_open() || file.eof())
			return false;

		uint32_t width, height;
		graphics::Channel channel;
		graphics::Component component;

		RE_CRITICAL_DBG_LOG(
			file.read((char*)&width, sizeof(width)),
			"read bitmap width",
			false);
		RE_CRITICAL_DBG_LOG(
			file.read((char*)&height, sizeof(height)),
			"read bitmap height",
			false);
		RE_CRITICAL_DBG_LOG(
			file.read((char*)&channel, sizeof(channel)),
			"read bitmap channel",
			false);
		RE_CRITICAL_DBG_LOG(
			file.read((char*)&component, sizeof(component)),
			"read bitmap component",
			false);
		RE_CRITICAL_DBG_LOG(
			size_t(channel) < RE_COUNT(graphics::Channel),
			"chek bitmap channel value",
			false);
		RE_CRITICAL_DBG_LOG(
			size_t(component) < RE_COUNT(graphics::Component),
			"check bitmap component value",
			false);

		m_content.alloc(channel, component, width * height);

		file.read((char*)m_content.data(), m_content.byte_size());

		return true;
	}

	void BitmapAsset::write_to_file(std::ofstream &file) const
	{
		RE_ASSERT(file.is_open());
		RE_ASSERT(m_content.exists());

		uint32_t width = m_content.width(), height = m_content.height();
		graphics::Channel channel = m_content.channel();
		graphics::Component component = m_content.component();
		
		write_asset_file_header(file);

		file.write((char*)&width, sizeof(width));
		file.write((char*)&height, sizeof(height));
		file.write((char*)&channel, sizeof(channel));
		file.write((char*)m_content.data(), m_content.byte_size());
	}
}