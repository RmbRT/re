#ifndef __re_fontasset_hpp_defined
#define __re_fontasset_hpp_defined

#include "Asset.hpp"
#include "ui/Font.hpp"

namespace re
{
	class FontAsset : public AssetBase
	{
		graphics::Bitmap atlas;
		std::unordered_map<uint32, ui::Font::Entry> entries;
		uint32 defaultEntry;
		uint lineHeight, tabWidth, spaceWidth;

	public:
		void writeToFile(std::ofstream &file) const;
		bool readFromFile(std::ifstream &file);

		unique_handle<ui::Font> createFont() const;
		void setFont(ui::Font const& font);
		void setFont(ui::Font && font);

	};
}

#endif