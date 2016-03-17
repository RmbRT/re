#ifndef __re_modelasset_hpp_defined
#define __re_modelasset_hpp_defined

#include "Asset.hpp"
#include "graphics\Vertex.hpp"
#include <vector>

namespace re
{
	class ModelAsset : public AssetBase
	{	friend class re::Resource;
		std::vector<graphics::Vertex> data;
		
		bool loadFromFile(std::ifstream &file);
		void writeToFile(std::ofstream &file) const;
	public:
		ModelAsset(const string &name, const std::vector<graphics::Vertex> &model);
		explicit ModelAsset(const std::vector<graphics::Vertex> &model);
		explicit ModelAsset(const string &name);
		ModelAsset();
	};
}

#endif