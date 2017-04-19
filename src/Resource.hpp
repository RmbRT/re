#ifndef __re_resource_hpp_defined
#define __re_resource_hpp_defined

#include "types.hpp"
#include "defines.hpp"
#include <vector>

#include "BitmapAsset.hpp"
#include "TextAsset.hpp"

namespace re
{
	class Resource
	{
		string8_t filename;
		bool loaded;

		std::vector<Shared<lock::ThreadSafe<TextAsset>>> texts;
		std::vector<Shared<lock::ThreadSafe<BitmapAsset>>> bitmaps;

		explicit Resource(
			string8_t const& filename);
	public:
		Resource();
		~Resource();

		bool load(
			string8_t const& filename);
		void writeToFile(
			string8_t const& filename);

		string8_t const& getFilename() const;


		bool isLoaded() const;

		/** Used for constructing Resources before writing them to a file. */
		Shared<lock::ThreadSafe<TextAsset>> addText(TextAsset &&asset);
		Shared<lock::ThreadSafe<BitmapAsset>> addBitmap(BitmapAsset &&asset);
	};
}
#endif