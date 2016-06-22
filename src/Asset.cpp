#include "Asset.hpp"
#include "LogFile.hpp"
#include <type_traits>

namespace re
{
	void AssetBase::writeAssetFileHeader(std::ofstream &file) const
	{
		size_t len = m_name.size() * sizeof(*m_name.data());
		file.write(_ADDRESSOF(m_type), sizeof(m_type));
		file.write(_ADDRESSOF(len), sizeof(len));
		file.write(m_name.data(), len);
	}

	bool AssetBase::loadAssetFileHeader(std::ifstream &file, AssetFileHeader &fileHeader)
	{
		file.read(_ADDRESSOF(fileHeader.type), sizeof(fileHeader.type));
		size_t len;
		file.read((char*)&len, sizeof(len));
		fileHeader.name.resize(len+1);
		file.read(&fileHeader.name.front(), len);
		fileHeader.name[len] = '\0';
		
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