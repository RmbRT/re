#include "Resource.hpp"
#include "Asset.hpp"
#include "LogFile.hpp"

#include "TextAsset.hpp"
#include "BitmapAsset.hpp"


namespace re
{
	Resource::Resource(
		string8_t const& filename):
		filename(filename),
		loaded(false),
		texts(0),
		bitmaps(0)
	{
		load(filename);
	}
	Resource::Resource():
		filename(),
		loaded(false),
		texts(0),
		bitmaps(0)
	{
	}

	Resource::~Resource()
	{
	}

	bool Resource::load(
		string8_t const& filename)
	{
		if(loaded)
		{
			RE_LOG("Resource::load: Resource already had data, discarding. (previous: %s, current: %s)", this->filename.c_str(), filename.c_str());
			texts.clear();
			bitmaps.clear();
			loaded = false;
		}
		std::ifstream file(filename.c_str(), std::ios::binary | std::ios::in);

		for(size_t index = 0; file; index++)
		{
			try
			{
				AssetFileHeader header;
				if(!AssetBase::load_asset_file_header(file, header))
				{
					RE_LOG("Resource::load: corrupt Asset file header #%i in %s", index, filename.c_str());
					file.close();
					return false;
				}
				else
				{
					switch(header.type)
					{
					case AssetType::AT_TEXT:
						{
							TextAsset asset(
								header.name,
								string8_t());
							if(!asset.load_from_file(file))
							{
								RE_LOG("Resource::load: corrupt Asset section of type TEXT #%i in %s", index, filename.c_str());
								file.close();
								return false;
							}
							else
								addText(std::move(asset));
						} break;
					case AssetType::AT_BITMAP:
						{
							BitmapAsset asset(header.name, graphics::Bitmap2D());
							if(!asset.load_from_file(file))
							{
								RE_LOG("corrupt Asset section of type BITMAP #%i in %s", index, filename.c_str());
								file.close();
								return false;
							}
							else
								addBitmap(std::move(asset));
						} break;
					default:
						{
							RE_LOG("unsupported Asset Type %i at #%i in %s", header.type, index, filename.c_str());
							file.close();
							return false;
						} break;
					}
				}
			} catch(...)
			{
				RE_LOG("exception.");
				std::abort();
			}
		}
		file.close();
		this->filename = filename;
		loaded = true;
		return true;
	}

	void Resource::writeToFile(
		string8_t const& filename)
	{
		std::ofstream file(filename.c_str(), std::ios::binary | std::ios::out);

		for(auto &text: texts)
			lock::read_lock(*text)->write_to_file(file);
		for(auto &bitmap: bitmaps)
			lock::read_lock(*bitmap)->write_to_file(file);

		file.close();
	}

	string8_t const& Resource::getFilename() const
	{
		return filename;
	}

	bool Resource::isLoaded() const
	{
		return loaded;
	}

	Shared<lock::ThreadSafe<TextAsset>> Resource::addText(TextAsset &&asset)
	{
		texts.push_back(Shared<lock::ThreadSafe<TextAsset>>::alloc(std::forward<TextAsset>(asset)));
		return texts.back();
	}
	Shared<lock::ThreadSafe<BitmapAsset>> Resource::addBitmap(BitmapAsset &&asset)
	{
		bitmaps.push_back(Shared<lock::ThreadSafe<BitmapAsset>>::alloc(std::forward<BitmapAsset>(asset)));
		return bitmaps.back();
	}
}