#include "BMPFile.hpp"

namespace re
{
	namespace file
	{
		enum COMPRESSION
		{
			BI_RGB = 0,
			BI_RLE8 = 1,
			BI_RLE4 = 2,
			BI_BITFIELDS = 3
		};

		struct BITMAPFILEHEADER
		{
			uint16 bfType; // "BM" (0x42 0x4d 19778)
			uint32 bfSize; // size in bytes
			uint32 bfReserved; //
			uint32 bfOffBits; //offset of image data.
		};

		struct BITMAPINFOHEADER
		{
			uint32 biSize;
			int32 biWidth;
			int32 biHeight;
			uint16 biPlanes;
			uint16 biBitCount;
			uint32 biCompression;
			uint32 biSizeImage;
			int32 biXPelsPerMeter;
			int32 biYPelsPerMeter;
			uint32 biClrUsed;
			uint32 biClrImportant;
		};
#define _addr(X) &reinterpret_cast<char&>(X)
#define _readobj(X) read(_addr(X), sizeof(X))
		graphics::Bitmap loadBMP(const std::string &file)
		{
			std::ifstream is(file, std::ios::binary | std::ios::in);

			BITMAPFILEHEADER fh;
			RE_ASSERT(is.read(_addr(fh), 14));
			uint32 HeaderSize;
			RE_ASSERT(is._readobj(HeaderSize));

			BITMAPINFOHEADER header;
			//RE_ASSERT(HeaderSize == 40);
			RE_ASSERT(is.read(_addr(header)+sizeof(header.biSize), 36));

			byte skip;
			for(size_t i = 0; i<HeaderSize-40; i++)
				RE_ASSERT(is._readobj(skip));

			RE_ASSERT(header.biBitCount == 8 || header.biBitCount >= 24);

			graphics::Bitmap data;
			switch(header.biBitCount)
			{
			case 8:
				{
					data.alloc(graphics::ColorChannel::BYTE1, header.biWidth, header.biHeight);
					is.read((char*)(data.getBaseAddress()), header.biWidth*header.biHeight);
					const size_t row_w = header.biWidth;

					std::vector<byte> row(row_w);

					for(size_t y = 0; y < header.biHeight; y++)
					{
						RE_ASSERT(is.read(_addr(row[0]), row.size()));
						for(size_t x = 0; x<header.biWidth; x++)
							data.getByte1(x,y) = row[x];
					}
				} break;
			case 24:
				{
					data.alloc(graphics::ColorChannel::BYTE3, header.biWidth, header.biHeight);
					const size_t off = (header.biWidth*3)&3;
					const size_t row_w = header.biWidth*3+off;

					std::vector<byte> row(row_w);
					for(size_t y = 0; y < header.biHeight; y++)
					{
						RE_ASSERT(is.read(_addr(row[0]), row.size()));
						for(size_t x = 0; x<header.biWidth; x++)
						{
							const size_t base_off = x+x+x;
							byte r = row[base_off+2];
							byte g = row[base_off+1];
							byte b = row[base_off];
							data.getByte3(x,y) = math::vec3<ubyte>(r,g,b);
						}
					}
				} break;
			case 32:
				{
					data.alloc(graphics::ColorChannel::BYTE4, header.biWidth, header.biHeight);
					const size_t row_w = header.biWidth*4;

					std::vector<byte> row(row_w);
					for(size_t y = 0; y < header.biHeight; y++)
					{
						RE_ASSERT(is.read(_addr(row[0]), row.size()));
						for(size_t x = 0; x<header.biWidth; x++)
						{
							const size_t base_off = x<<2;
							byte a = row[base_off+3];
							byte r = row[base_off+2];
							byte g = row[base_off+1];
							byte b = row[base_off];

							data.getByte4(x,y) = math::vec4<ubyte>(r,g,b,a);
						}
					}
				} break;
			default:
				{
					RE_ASSERTION_FAILURE("UNABLE TO READ BITMAP FILE: INVALID BPP");
				} break;
			}
			return data;
		}
	}
}