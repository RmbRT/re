#ifndef __re_textasset_hpp_defined
#define __re_textasset_hpp_defined

#include "Asset.hpp"

namespace re
{

	/** A TextAsset contains a string. It can be used for localization and other cases of text loading. */
	class TextAsset: public AssetBase
	{	friend class Resource;
		string content;

		bool loadFromFile(std::ifstream &file);
		void writeToFile(std::ofstream &file) const;

	public:
		TextAsset(const string &name, const string &text);
		TextAsset();

		const string &getText() const;
		void setText(const string &text);
	};
}

#endif