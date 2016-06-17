#include "ModelAsset.hpp"

namespace re
{
	ModelAsset::ModelAsset(): AssetBase(AssetType::AT_MODEL), data()	{	}
	ModelAsset::ModelAsset(const string &name, const std::vector<graphics::Vertex> &model): AssetBase(name, AssetType::AT_MODEL), data(model)	{	}
	ModelAsset::ModelAsset(const std::vector<graphics::Vertex> &model): AssetBase(AssetType::AT_MODEL), data(model)	{	}
	ModelAsset::ModelAsset(const string &name): AssetBase(name, AssetType::AT_MODEL), data()	{	}

	void ModelAsset::writeToFile(std::ofstream &file) const
	{
		RE_ASSERT(file.is_open());

		size_t size = data.size();
		file.write(_ADDRESSOF(size), sizeof(size));
		file.write(_ADDRESSOF(data[0]), sizeof(data[0])*size);
	}
	bool ModelAsset::loadFromFile(std::ifstream &file)
	{
		if(!file.is_open())
			return false;
		size_t size;
		file.read((char*)&size, sizeof(size));
		data.clear();
		data.resize(size);
		file.read((char*)&data[0], sizeof(data[0])*size);
		return true;
	}
}