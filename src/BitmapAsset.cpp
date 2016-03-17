#include "BitmapAsset.hpp"
#include "LogFile.hpp"

namespace re
{
	BitmapAsset::BitmapAsset() : content(), AssetBase(string(), AssetType::AT_BITMAP)	{	}
	BitmapAsset::BitmapAsset(const string &name, const graphics::Bitmap &content):
		AssetBase(name, AssetType::AT_BITMAP), content(content)	{	}
	BitmapAsset::BitmapAsset(const graphics::Bitmap &content): AssetBase(string(), AssetType::AT_BITMAP), content(content)	{	}
	BitmapAsset::BitmapAsset(const string &name) : AssetBase(name, AssetType::AT_BITMAP), content()	{	}

	bool BitmapAsset::loadFromFile(std::ifstream &file)
	{
		if(!file.is_open() || file.eof())
			return false;

		uint32 width, height;
		int channel;

		file.read((char*)&width, sizeof(width));
		file.read((char*)&height, sizeof(height));
		file.read((char*)&channel, sizeof(channel));

		graphics::ColorChannel _channel;
		switch(channel)
		{
		case (int)graphics::ColorChannel::FLOAT1:
			{
				_channel = graphics::ColorChannel::FLOAT1;
			} break;
		case (int)graphics::ColorChannel::FLOAT2:
			{
				_channel = graphics::ColorChannel::FLOAT2;
			} break;
		case (int)graphics::ColorChannel::FLOAT3:
			{
				_channel = graphics::ColorChannel::FLOAT3;
			} break;
		case (int)graphics::ColorChannel::FLOAT4:
			{
				_channel = graphics::ColorChannel::FLOAT4;
			} break;
		case (int) graphics::ColorChannel::BYTE1:
			{
				_channel = graphics::ColorChannel::BYTE1;
			} break;
		case (int) graphics::ColorChannel::BYTE2:
			{
				_channel = graphics::ColorChannel::BYTE2;
			} break;
		case (int)graphics::ColorChannel::BYTE3:
			{
				_channel = graphics::ColorChannel::BYTE3;
			} break;
		case (int)graphics::ColorChannel::BYTE4:
			{
				_channel = graphics::ColorChannel::BYTE4;
			} break;
		default:
			{
				RE_ASSERTION_FAILURE("int to re::graphics::ColorChannel: invalid value.");
			} break;
		}
		content.alloc(_channel, width, height);

		file.read((char*)content.getBaseAddress(), content.getByteSize());

		return true;
	}

	void BitmapAsset::writeToFile(std::ofstream &file) const
	{
		RE_ASSERT(file.is_open());

		uint32 width = content.getWidth(), height = content.getHeight();
		int channel = (int) content.getChannel();
		
		writeAssetFileHeader(file);

		file.write((char*)&width, sizeof(width));
		file.write((char*)&height, sizeof(height));
		file.write((char*)&channel, sizeof(channel));
		file.write((char*)content.getBaseAddress(), content.getByteSize());
	}

	const graphics::Bitmap &BitmapAsset::getBitmap() const
	{
		return content;
	}
	void BitmapAsset::setBitmap(const graphics::Bitmap &bitmap)
	{
		content = bitmap;
	}
}