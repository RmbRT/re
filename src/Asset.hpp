#ifndef __re_asset_hpp_defined
#define __re_asset_hpp_defined

#include "types.hpp"
#include <fstream>


namespace re
{

	enum class AssetType
	{
		/** Used by text-based Assets.*/
		AT_TEXT,
		/** Used by image-based Assets.*/
		AT_BITMAP,
		/** Used by geometry-based Assets.*/
		AT_MODEL,
		/** Used by texture-based Assets.*/
		AT_TEXTURE,

		/** This is for user made Asset types.
		They have to use this type to correspond to the Resource File protocol.*/
		AT_CUSTOM
	};

	/** The header structure of an Asset that is written into the file before the Asset.*/
	struct AssetFileHeader
	{
		/** The name of the Asset.*/
		string name;
		/** The type of the Asset.*/
		AssetType type;
	};
	class AssetBase
	{	friend class Resource;
		string name;
		AssetType type;
	public:
		AssetBase(const string &name, AssetType type);
		AssetBase(AssetType type);

		const string &getName() const;
		void setName(const string &name);
		bool hasName() const;

		AssetType getType() const;

		void writeAssetFileHeader(std::ofstream &file) const;
		static bool loadAssetFileHeader(std::ifstream &file, AssetFileHeader &fileHeader);
	};
}

#endif
