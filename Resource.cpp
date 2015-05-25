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
								addText(std::move(asset));
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
								addBitmap(std::move(asset));
						} break;
					case AssetType::AT_MODEL:
						{
							ModelAsset asset(header.name);
							if(!asset.loadFromFile(file))
							{
								LogFile::GetInst()->writefln("Resource::load: corrupt Asset section of type MODEL %i in %s", index, filename.c_str());
								file.close();
								return false;
							}
							else
								addModel(std::move(asset));
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
			text->readLock()->writeToFile(file);
		for(auto &model: models)
			model->readLock()->writeToFile(file);
		for(auto &bitmap: bitmaps)
			bitmap->readLock()->writeToFile(file);

		file.close();
	}

	const string &Resource::getFilename() const
	{
		return filename;
	}

	bool Resource::isLoaded() const
	{
		return loaded;
	}

	strong_handle<ThreadSafe<ModelAsset>> Resource::addModel(ModelAsset &&asset)
	{
		models.push_back(alloc<ThreadSafe<ModelAsset>>(std::forward<ModelAsset>(asset)));
		return models.back();
	}
	strong_handle<ThreadSafe<TextAsset>> Resource::addText(TextAsset &&asset)
	{
		texts.push_back(alloc<ThreadSafe<TextAsset>>(std::forward<TextAsset>(asset)));
		return texts.back();
	}
	strong_handle<ThreadSafe<BitmapAsset>> Resource::addBitmap(BitmapAsset &&asset)
	{
		bitmaps.push_back(alloc<ThreadSafe<BitmapAsset>>(std::forward<BitmapAsset>(asset)));
		return bitmaps.back();
	}
}