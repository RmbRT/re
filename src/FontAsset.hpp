#ifndef __re_fontasset_hpp_defined
#define __re_fontasset_hpp_defined

#include "Asset.hpp"
#include "ui/Font.hpp"

namespace re
{
	class FontAsset : public AssetBase
	{
		graphics::Bitmap2D atlas;
		std::unordered_map<uint32_t, ui::Font::Entry> entries;
		uint32_t defaultEntry;
		uint_t lineHeight, tabWidth, spaceWidth;

	public:
		void writeToFile(std::ofstream &file) const;
		bool readFromFile(std::ifstream &file);

		Shared<ui::Font> createFont() const;
		void setFont(ui::Font const& font);
		void setFont(ui::Font && font);

	};
}

#endif