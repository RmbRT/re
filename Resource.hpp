#ifndef __re_resource_hpp_defined
#define __re_resource_hpp_defined

#include "types.hpp"
#include "defines.hpp"
#include <vector>
#include "util/Lock/Lock.hpp"

#include "BitmapAsset.hpp"
#include "ModelAsset.hpp"
#include "TextAsset.hpp"

namespace re
{
	class Resource
	{
		string filename;
		bool loaded;
		
		std::vector<strong_handle<ThreadSafe<ModelAsset>>> models;
		std::vector<strong_handle<ThreadSafe<TextAsset>>> texts;
		std::vector<strong_handle<ThreadSafe<BitmapAsset>>> bitmaps;
		
		explicit Resource(const string &filename);
	public:
		Resource();
		~Resource();

		bool load(const string &filename);
		void writeToFile(const string &filename);

		const string &getFilename() const;


		bool isLoaded() const;

		/*Used for constructing Resources before writing them to a file.*/
		strong_handle<ThreadSafe<ModelAsset>> addModel(ModelAsset &&asset);
		strong_handle<ThreadSafe<TextAsset>> addText(TextAsset &&asset);
		strong_handle<ThreadSafe<BitmapAsset>> addBitmap(BitmapAsset &&asset);
	};
}
#endif