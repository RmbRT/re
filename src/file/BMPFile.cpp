#include "BMPFile.hpp"
#include "../util/Error.hpp"
#include <fstream>

namespace re
{
	namespace file
	{
		enum Compression
		{
			Rgb = 0,
			Rle8 = 1,
			Rle4 = 2,
			Bitfields = 3
		};

		struct BitmapFileHeader
		{
			uint16_t m_type; // "BM" (0x42 0x4d, 19778)
			uint32_t m_size; // size in bytes
			uint32_t m_reserved; //
			uint32_t m_off_bits; //offset of image data.
		};

		struct BitmapInfoHeader
		{
			uint32_t m_size;
			int32_t m_width;
			int32_t m_height;
			uint16_t m_planes;
			uint16_t m_bit_count;
			uint32_t m_compression;
			uint32_t m_size_image;
			int32_t m_x_pels_per_meter;
			int32_t m_y_pels_per_meter;
			uint32_t m_clr_used;
			uint32_t m_clr_important;
		};

#define _addr(X) &reinterpret_cast<char&>(X)
#define _readobj(X) read(_addr(X), sizeof(X))

		bool load_bmp(char const* file, graphics::Bitmap2D & out)
		{
			std::ifstream is(file, std::ios::binary | std::ios::in);

			BitmapFileHeader fh;
			RE_CRITICAL_DBG_LOG(is.read(_addr(fh), 14),
				"read bitmap file header", false);

			uint32_t headerSize;
			RE_CRITICAL_DBG_LOG(is._readobj(headerSize),
				"read bitmap header size", false);

			BitmapInfoHeader header;
			//CRITICAL(HeaderSize == 40, false);
			RE_CRITICAL_DBG_LOG(is.read(_addr(header)+sizeof(header.m_size), 36),
				"read bitmap info header", false);

			byte_t skip;
			for(size_t i = 0; i<headerSize-40; i++)
				RE_CRITICAL_DBG_LOG(is._readobj(skip),
					"skip unused bytes", false);

			RE_CRITICAL_DBG_LOG(header.m_bit_count == 8 || header.m_bit_count >= 24,
				"unsupported bitmap bits", false);

			RE_CRITICAL_DBG_LOG(header.m_compression == Compression::Rgb,
				"check for supported compression", false);

			switch(header.m_bit_count)
			{
			case 8:
				{
					out.alloc(
						graphics::Channel::kR,
						graphics::Component::kUbyte,
						header.m_width,
						header.m_height);

					const size_t row_w = header.m_width;

					std::vector<ubyte_t> row(row_w);

					for(uint32_t y = 0; y < header.m_height; y++)
					{
						RE_CRITICAL_DBG_LOG(is.read(_addr(row[0]), row.size()),
							"read pixel row", false);
						for(uint32_t x = 0; x<header.m_width; x++)
							out.pixel<
								graphics::Channel::kR,
								graphics::Component::kUbyte>(x,y)
								= row[x];
					}
				} break;
			case 24:
				{
					out.alloc(
						graphics::Channel::kRgb,
						graphics::Component::kUbyte,
						header.m_width,
						header.m_height);

					size_t const off = (header.m_width*3)&3;
					size_t const row_w = header.m_width*3+off;

					std::vector<ubyte_t> row(row_w);
					for(uint32_t y = 0; y < header.m_height; y++)
					{
						RE_CRITICAL_DBG_LOG(is.read(_addr(row[0]), row.size()),
							"read pixel row", false);
						for(uint32_t x = 0; x<header.m_width; x++)
						{
							const size_t base_off = 3*x;
							ubyte_t r = row[base_off+2];
							ubyte_t g = row[base_off+1];
							ubyte_t b = row[base_off];
							out.pixel<
								graphics::Channel::kRgb,
								graphics::Component::kUbyte>(x,y)
								= math::Vec3<ubyte_t>(r,g,b);
						}
					}
				} break;
			case 32:
				{
					out.alloc(
						graphics::Channel::kRgba,
						graphics::Component::kUbyte,
						header.m_width,
						header.m_height);

					size_t const row_w = header.m_width<<2;

					std::vector<ubyte_t> row(row_w);
					for(size_t y = 0; y < header.m_height; y++)
					{
						RE_CRITICAL_DBG_LOG(is.read(_addr(row[0]), row.size()),
							"read pixel row", false);
						for(size_t x = 0; x<header.m_width; x++)
						{
							const size_t base_off = x<<2;
							byte_t a = row[base_off+3];
							byte_t r = row[base_off+2];
							byte_t g = row[base_off+1];
							byte_t b = row[base_off];

							out.pixel<
								graphics::Channel::kRgba,
								graphics::Component::kUbyte>(x,y)
								= math::Vec4<ubyte_t>(r,g,b,a);
						}
					}
				} break;
			default:
				{
					RE_CRITICAL_DBG_LOG(false,
						"identify channel count", false);
				} break;
			}
			return true;
		}
	}
}