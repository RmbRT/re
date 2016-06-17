#ifndef __re_bitmapasset_hpp_defined
#define __re_bitmapasset_hpp_defined

#include "Asset.hpp"
#include "graphics/Bitmap.hpp"

#include "types.hpp"
#include "defines.hpp"

namespace re
{
	class BitmapAsset : public AssetBase
	{	friend class Resource;
		graphics::Bitmap content;

		bool loadFromFile(std::ifstream &file);
		void writeToFile(std::ofstream &file) const;

	public:
		BitmapAsset();
		BitmapAsset(const string &name, const graphics::Bitmap &content);
		BitmapAsset(const string &name);
		BitmapAsset(const graphics::Bitmap &content);

		const graphics::Bitmap &getBitmap() const;
		void setBitmap(const graphics::Bitmap &bitmap);
	};
}

#endif