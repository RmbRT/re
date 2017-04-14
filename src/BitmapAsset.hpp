#ifndef __re_bitmapasset_hpp_defined
#define __re_bitmapasset_hpp_defined

#include "Asset.hpp"
#include "graphics/Bitmap.hpp"

#include "types.hpp"
#include "defines.hpp"

namespace re
{
	/** An asset type that contains a Bitmap. */
	class BitmapAsset : public AssetBase
	{	friend class Resource;
		/** The content of the asset. */
		graphics::Bitmap2D m_content;

		/** Loads the asset from a file.
		@param[in] file:
			The file stream to load the asset from.
		@return
			Whether the asset could be successfully loaded. */
		bool load_from_file(
			std::ifstream &file);
		/** Writes the asset to a file.
		@param[in] file:
			The file stream to write the asset to. */
		void write_to_file(
			std::ofstream &file) const;

	public:
		/** Creates a bitmap asset without name or content. */
		RECX BitmapAsset();
		/** Creates a bitmap asset with the given name and content.
		@param[in] name:
			The name string of the asset.
		@param[in] content:
			The bitmap of the asset. */
		REIL BitmapAsset(
			string8_t name,
			graphics::Bitmap2D content);
		/** Creates a bitmap asset with the given name but no content.
		@param[in] name:
			The name string of the asset. */
		REIL BitmapAsset(
			string8_t name);
		/** Creates an unnamed bitmap asset with the given content.
		@param[in] content:
			The bitmap of the asset. */
		REIL BitmapAsset(
			graphics::Bitmap2D content);
		/** @return
			the bitmap of the asset. */
		REIL graphics::Bitmap2D const& bitmap() const;
		REIL graphics::Bitmap2D & bitmap();
	};
}

#include "BitmapAsset.inl"

#endif