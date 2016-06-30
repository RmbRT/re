#ifndef __re_asset_hpp_defined
#define __re_asset_hpp_defined

#include "types.hpp"
#include <fstream>


namespace re
{
	/** Used for serializing Assets. */
	enum class AssetType
	{
		/** Used by text-based Assets. */
		AT_TEXT,
		/** Used by image-based Assets. */
		AT_BITMAP,
		/** Used by geometry-based Assets. */
		AT_MODEL,
		/** Used by texture-based Assets. */
		AT_TEXTURE,

		/** This is for user made Asset types.
			They have to use this type to correspond to the Resource File protocol.
			This indicates that the engine does not know how to load the Asset. */
		AT_CUSTOM
	};

	/** The header structure of an Asset that is written into the file before the Asset. */
	struct AssetFileHeader
	{
		/** The name of the Asset. */
		Utf8String name;
		/** The type of the Asset. */
		AssetType type;
	};

	/** The base class used by all Asset types. */
	class AssetBase
	{	friend class Resource;
		/** The name of the Asset. */
		Utf8String m_name;
	public:
		/** Constructs an Asset with the given name and the given type.
		@param[in] name:
			The name of the Asset.*/
		REIL AssetBase(Utf8String name);

		/** Constructs an unnamed asset. */
		RECX AssetBase();

		AssetBase(AssetBase && move) = default;
		AssetBase &operator=(AssetBase &&) = default;
		virtual ~AssetBase() = 0;

		/** @return The name of this Asset. */
		Utf8String const& name() const;
		/** @return The name of this Asset. */
		Utf8String & name();
		/** Whether this Asset has a name. */
		bool has_name() const;

		/** Returns the type of the Asset. */
		virtual AssetType type() const = 0;

		/** Writes an AssetFileHeader describing this Asset to the given file stream. */
		void write_asset_file_header(std::ofstream &file) const;
		/** Loads an AssetFileHeader describing this Asset from the given file stream. */
		static bool load_asset_write_header(std::ifstream &file, AssetFileHeader &fileHeader);
	};
}

#include "Asset.inl"

#endif
