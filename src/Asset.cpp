#include "Asset.hpp"
#include "LogFile.hpp"
#include <type_traits>

#define _CADDRESSOF(X) (&reinterpret_cast<char const&>(X))
#define _ADDRESSOF(X) (&reinterpret_cast<char &>(X))

namespace re
{
	void AssetBase::writeAssetFileHeader(std::ofstream &file) const
	{
		size_t len = m_name.size() * sizeof(*m_name.data());
		AssetType const& type = this->type();
		file.write(_CADDRESSOF(type), sizeof(type));
		file.write(_CADDRESSOF(len), sizeof(len));
		file.write(_CADDRESSOF(*m_name.data()), len);
	}

	bool AssetBase::loadAssetFileHeader(std::ifstream &file, AssetFileHeader &fileHeader)
	{
		file.read(_ADDRESSOF(fileHeader.type), sizeof(fileHeader.type));
		size_t len;
		file.read(_ADDRESSOF(len), sizeof(len));
		fileHeader.name.resize(len+1);
		file.read(_ADDRESSOF(*fileHeader.name.data()), len);
		
		switch(fileHeader.type)
		{
		case AssetType::AT_TEXT:
		case AssetType::AT_BITMAP:
		case AssetType::AT_MODEL:
		case AssetType::AT_TEXTURE:
		case AssetType::AT_CUSTOM:
			{
				return true;
			} break;
		default: return false;
		}
	}
}