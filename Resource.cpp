#include "Resource.hpp"
#include "Asset.hpp"
#include "LogFile.hpp"

#include "TextAsset.hpp"
#include "BitmapAsset.hpp"
#include "ModelAsset.hpp"


namespace re
{
	Resource::Resource(const string &filename):
		filename(filename), loaded(false), texts(0), bitmaps(0), models(0)
	{
		load(filename);
	}
	Resource::Resource(): filename(), loaded(false), texts(0), bitmaps(0), models(0)	{	}

	Resource::~Resource()
	{
	}

	bool Resource::load(const string &filename)
	{
		if(loaded)
		{
			LogFile::GetInst()->writefln("Resource::load: Resource already had data, discarding. (previous: %s, current: %s)", this->filename.c_str(), filename.c_str());
			texts.clear();
			bitmaps.clear();
			models.clear();
			loaded = false;
		}
		std::ifstream file(filename.c_str(), std::ios::binary | std::ios::in);

		for(size_t index = 0; file; index++)
		{
			try
			{
				AssetFileHeader header;
				if(!AssetBase::loadAssetFileHeader(file, header))
				{
					LogFile::GetInst()->writefln("Resource::load: corrupt Asset file header #%i in %s", index, filename.c_str());
					file.close();
					return false;
				}
				else
				{
					switch(header.type)
					{
					case AssetType::AT_TEXT:
						{
							TextAsset asset(header.name, std::string());
							if(!asset.loadFromFile(file))
							{
								LogFile::GetInst()->writefln("Resource::load: corrupt Asset section of type TEXT #%i in %s", index, filename.c_str());
								file.close();
								return false;
							}
							else
								addAsset(asset);
						} break;
					case AssetType::AT_BITMAP:
						{
							BitmapAsset asset(header.name, graphics::Bitmap());
							if(!asset.loadFromFile(file))
							{
								LogFile::GetInst()->writefln("Resource::load: corrupt Asset section of type BITMAP #%i in %s", index, filename.c_str());
								file.close();
								return false;
							}
							else
								addAsset(asset);
						} break;
					default:
						{
							LogFile::GetInst()->writefln("Resource::load: unsupported Asset Type %i at #%i in %s", header.type, index, filename.c_str());
							file.close();
							return false;
						} break;
					}
				}
			} catch(...)
			{
				LogFile::GetInst()->writefln("Resource::load: exception.");
				std::abort();
			}
		}
		file.close();
		this->filename = filename;
		loaded = true;
		return true;
	}

	void Resource::writeToFile(const string &filename)
	{
		std::ofstream file(filename.c_str(), std::ios::binary | std::ios::out);
		
		for(auto &text: texts)
			text.writeToFile(file);
		for(auto &model: models)
			model.writeToFile(file);
		for(auto &bitmap: bitmaps)
			bitmap.writeToFile(file);

		file.close();
	}

	const string &Resource::getFilename() const
	{
		return filename;
	}
	unsafe<const AssetBase> Resource::getAsset(const string &name) const
	{
		RE_ASSERT(!name.empty());

		for (auto &asset : models)
			if (asset.getName() == name.c_str())
				return cast<const ModelAsset>(&asset);
		return nullptr;
	}
	unsafe<AssetBase> Resource::getAsset(const string &name)
	{
		RE_ASSERT(!name.empty());

		for (auto &asset : models)
			if (asset.getName() == name.c_str())
				return cast<ModelAsset>(&asset);
		return nullptr;
	}


	bool Resource::isLoaded() const
	{
		return loaded;
	}

	notnull<AssetBase> Resource::addAsset(notnull<AssetBase> asset)
	{
		switch(asset->getType())
		{
		case AssetType::AT_MODEL:
			models.push_back(cast<ModelAsset>(asset));
			return models.back();
			break;
		case AssetType::AT_TEXT:
			texts.push_back(cast<TextAsset>(asset));
			return texts.back();
			break;
		case AssetType::AT_BITMAP:
			bitmaps.push_back(cast<BitmapAsset>(asset));
			return bitmaps.back();
			break;
		default:
			RE_ASSERTION_FAILURE("INVALID/UNIMPLEMENTED ASSET TYPE");
		}
	}
}