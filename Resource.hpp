#ifndef __re_resource_hpp_defined
//#define __re_resource_hpp_defined

#include "types.hpp"
#include "defines.hpp"
#include <vector>


#include "BitmapAsset.hpp"
#include "ModelAsset.hpp"
#include "TextAsset.hpp"

namespace re
{
	class Resource
	{
		string filename;
		bool loaded;
		
		std::vector<ModelAsset> models;
		std::vector<TextAsset> texts;
		std::vector<BitmapAsset> bitmaps;
		
		explicit Resource(const string &filename);
	public:
		Resource();
		~Resource();

		bool load(const string &filename);
		void writeToFile(const string &filename);

		const string &getFilename() const;

		unsafe<AssetBase> getAsset(size_t index);
		unsafe<const AssetBase> getAsset(size_t index) const;
		unsafe<AssetBase> getAsset(const string &name);
		unsafe<const AssetBase> getAsset(const string &name) const;

		size_t getAssetCount() const;

		bool isLoaded() const;

		/*Used for constructing Resources before writing them to a file.*/
		notnull<AssetBase> addAsset(notnull<AssetBase> asset);
	};
}
#endif