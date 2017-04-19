#ifndef __re_textasset_hpp_defined
#define __re_textasset_hpp_defined

#include "Asset.hpp"

namespace re
{

	/** A TextAsset contains a string. It can be used for localization and other cases of text loading. */
	class TextAsset: public AssetBase
	{	friend class Resource;
		string8_t content;

		bool load_from_file(std::ifstream &file);
		void write_to_file(std::ofstream &file) const;

	public:
		TextAsset(
			string8_t const& name,
			string8_t const& text);
		TextAsset();

		string8_t const& getText() const;
		void setText(
			string8_t const&text);

		AssetType type() const override;
	};
}

#endif