#include "TextAsset.hpp"

namespace re
{
	TextAsset::TextAsset(
		string8_t const& name,
		string8_t const& text):
		AssetBase(
			name),
		content(text)
	{
	}

	TextAsset::TextAsset():
		AssetBase(),
		content()
	{
	}

	bool TextAsset::load_from_file(
		std::ifstream &file)
	{
		if(!file.is_open())
			return false;

		size_t len;
		file.read((char*)&len, sizeof(len));
		content.resize(len+1);
		file.read(content.c_data(), len);
		content[len] = '\0';
		return true;
	}
	void TextAsset::write_to_file(
		std::ofstream &file) const
	{
		write_asset_file_header(file);

		size_t len = content.length();
		file.write((char*)&len, sizeof(len));
		file.write(content.c_data(), len);
	}

	string8_t const& TextAsset::getText() const
	{
		return content;
	}

	void TextAsset::setText(
		string8_t const& text)
	{
		content = text;
	}

	AssetType TextAsset::type() const
	{
		return AssetType::AT_TEXT;
	}
}