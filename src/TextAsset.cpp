#include "TextAsset.hpp"

namespace re
{
	TextAsset::TextAsset(const string &name, const string &text):
		AssetBase(name, AssetType::AT_TEXT), content(text)	{	}
	TextAsset::TextAsset(): AssetBase(AssetType::AT_TEXT), content()	{	}

	bool TextAsset::loadFromFile(std::ifstream &file)
	{
		if(!file.is_open())
			return false;

		size_t len;
		file.read((char*)&len, sizeof(len));
		content.resize(len+1);
		file.read((char*)&content.front(), len);
		content[len] = '\0';
		return true;
	}
	void TextAsset::writeToFile(std::ofstream &file) const
	{
		writeAssetFileHeader(file);
		
		size_t len = content.length();
		file.write(_ADDRESSOF(len), sizeof(len));
		file.write(content.c_str(), len);
	}

	const string &TextAsset::getText() const
	{
		return content;
	}

	void TextAsset::setText(const string &text)
	{
		content.assign(text);
	}
}