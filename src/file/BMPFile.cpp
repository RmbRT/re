#include "BMPFile.hpp"
#include "../util/Error.hpp"

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
		bool loadBMP(std::string const& file, Bitmap & out)
		{
			std::ifstream is(file, std::ios::binary | std::ios::in);

			BITMAPFILEHEADER fh;
			CRITICAL(is.read(_addr(fh), 14), false);
			uint32 HeaderSize;
			CRITICAL(is._readobj(HeaderSize), false);

			BITMAPINFOHEADER header;
			//CRITICAL(HeaderSize == 40, false);
			CRITICAL(is.read(_addr(header)+sizeof(header.biSize), 36));

			byte skip;
			for(size_t i = 0; i<HeaderSize-40; i++)
				CRITICAL(is._readobj(skip), false);

			CRITICAL(header.biBitCount == 8 || header.biBitCount >= 24, false);

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
						CRITICAL(is.read(_addr(row[0]), row.size()), false);
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
						CRITICAL(is.read(_addr(row[0]), row.size()), false);
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
						CRITICAL(is.read(_addr(row[0]), row.size()), false);
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
					return false;
				} break;
			}
			return data;
		}
	}
}