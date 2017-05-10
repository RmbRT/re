#include "TextAsset.hpp"

namespace re
{
	TextAsset::TextAsset(
		string8_t const& name,
		string8_t const& text):
		AssetBase(name),
		m_content(text)
	{
	}

	TextAsset::TextAsset():
		AssetBase(),
		m_content()
	{
	}

	bool TextAsset::load_from_file(
		std::ifstream &file)
	{
		if(!file.is_open())
			return false;

		size_t len;
		file.read((char*)&len, sizeof(len));
		m_content.resize(len);
		file.read(m_content.c_data(), len);
		m_content[len] = '\0';
		return true;
	}
	void TextAsset::write_to_file(
		std::ofstream &file) const
	{
		write_asset_file_header(file);

		size_t len = m_content.length();
		file.write((char*)&len, sizeof(len));
		file.write(m_content.c_data(), len);
	}

	AssetType TextAsset::type() const
	{
		return AssetType::AT_TEXT;
	}
}