#include "Asset.hpp"
#include "LogFile.hpp"

namespace re
{
	AssetBase::AssetBase(AssetType type): name(), type(type)	{	}
	AssetBase::AssetBase(const string &name, AssetType type): name(name), type(type)	{	}

	const string &AssetBase::getName() const
	{
		return name;
	}

	void AssetBase::setName(const string &name)
	{
		this->name = name;
	}

	bool AssetBase::hasName() const
	{
		return !name.empty();
	}


	void AssetBase::writeAssetFileHeader(std::ofstream &file) const
	{
		AssetFileHeader header = { name, type };
		size_t len = name.length();
		file.write(_ADDRESSOF(header.type), sizeof(header.type));
		file.write(_ADDRESSOF(len), sizeof(len));
		file.write(name.c_str(), len);
	}

	bool AssetBase::loadAssetFileHeader(std::ifstream &file, AssetFileHeader &fileHeader)
	{
		file.read((char*)&fileHeader.type, sizeof(fileHeader.type));
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

	AssetType AssetBase::getType() const { return type; }
}