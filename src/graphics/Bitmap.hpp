#ifndef __re_bitmap_hpp_defined
#define __re_bitmap_hpp_defined

#include "../types.hpp"
#include "../defines.hpp"
#include "../math/Vector.hpp"
namespace re
{
	namespace graphics
	{
		/** Filter method useed to generate a mipmap. */
		enum class MipmapFilter
		{
			Center,
			Adjacent4,
			Adjacent8
		};

		/** Internal data types used by a Bitmap. */
		enum class ColorChannel
		{
			FLOAT1,
			FLOAT2,
			FLOAT3,
			FLOAT4,
			BYTE1,
			BYTE2,
			BYTE3,
			BYTE4
		};

		/** Represents an Image. */
		class Bitmap
		{
			size_t m_bytes;
			ColorChannel m_channel;
			uint32 m_width;
			uint32 m_height;

			void* m_pixels;

		public:
			Bitmap();
			Bitmap(Bitmap const& bitmap);
			Bitmap(ColorChannel channel, uint32 width, uint32 height);
			Bitmap(Bitmap &&move);
			~Bitmap();

			/** Allocates a bitmap with the given channels and bounds.*/
			void alloc(ColorChannel channel, uint32 widh, uint32 height);

			Bitmap &operator=(Bitmap const& bitmap);
			Bitmap &operator=(Bitmap && bitmap);

			uint32 getWidth() const;
			uint32 getHeight() const;
			ColorChannel getChannel() const;

			Bitmap generateMipMap(MipmapFilter filter) const;


			size_t getByteSize() const;

			void* getBaseAddress();
			const void* getBaseAddress() const;

			/*Returns a float 1 channeled color at the given location.*/
			float &getFloat1(uint32 x, uint32 y);
			/*Reurns a float 2 channeled color at the given location.*/
			math::vec2<float> &getFloat2(uint32 x, uint32 y);
			/*Returns a float 3 channeled color at the given location.*/
			math::vec3<float> &getFloat3(uint32 x, uint32 y);
			/*Returns a float 4 channeled color at the given location.*/
			math::vec4<float> &getFloat4(uint32 x, uint32 y);
			/*Returns a byte 1 channeled color at the given location.*/
			ubyte &getByte1(uint32 x, uint32 y);
			/*Returns a byte 2 channeled color at the given location*/
			math::vec2<ubyte> &getByte2(uint32 x, uint32 y);
			/*Returns a byte 3 channeled color at the given location.*/
			math::vec3<ubyte> &getByte3(uint32 x, uint32 y);
			/*Returns a byte 4 channeled color at the given location.*/
			math::vec4<ubyte> &getByte4(uint32 x, uint32 y);

			/*Returns a float 1 channeled color at the given location.*/
			const float &getFloat1(uint32 x, uint32 y) const;
			/*Reurns a float 2 channeled color at the given location.*/
			const math::vec2<float> &getFloat2(uint32 x, uint32 y) const;
			/*Returns a float 3 channeled color at the given location.*/
			const math::vec3<float> &getFloat3(uint32 x, uint32 y) const;
			/*Returns a float 4 channeled color at the given location.*/
			const math::vec4<float> &getFloat4(uint32 x, uint32 y) const;
			/*Returns a byte 1 channeled color at the given location.*/
			const ubyte &getByte1(uint32 x, uint32 y) const;
			/*Returns a byte 2 channeled color at the given location*/
			const math::vec2<ubyte> &getByte2(uint32 x, uint32 y) const;
			/*Returns a byte 3 channeled color at the given location.*/
			const math::vec3<ubyte> &getByte3(uint32 x, uint32 y) const;
			/*Returns a byte 4 channeled color at the given location.*/
			const math::vec4<ubyte> &getByte4(uint32 x, uint32 y) const;

		};
	}
}


#endif