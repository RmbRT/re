#include "Bitmap.hpp"
#include "../LogFile.hpp"

namespace re
{
	namespace graphics
	{
		Bitmap::Bitmap(Bitmap const& bitmap):
			width(bitmap.width),
			height(bitmap.height),
			channel(bitmap.channel),
			pixels(nullptr)
		{
			size_t size = getByteSize();
			pixels = new byte[size];
			memcpy(pixels, bitmap.pixels, size);
		}

		Bitmap::Bitmap():
			channel(ColorChannel::BYTE4),
			width(0),
			height(0),
			pixels(nullptr)
		{
		}
		
		Bitmap::Bitmap(ColorChannel channel, uint32 width, uint32 height):
			width(width),
			height(height),
			channel(channel),
			pixels(nullptr)
		{
			alloc(channel, width, height);
		}

		Bitmap::Bitmap(Bitmap &&move):
			channel(move.channel),
			width(move.width),
			height(move.height),
			pixels(move.pixels)
		{
			move.pixels = nullptr;
			move.width = move.height = 0;
		}
		
		Bitmap::~Bitmap()
		{
			if(pixels)
			{
				delete []pixels;
				pixels = nullptr;
			}
		}

		void Bitmap::alloc(ColorChannel channel, uint32 width, uint32 height)
		{
			this->channel = channel;
			this->width = width;
			this->height = height;

			if(pixels)
				delete[] pixels;
			pixels = new byte[getByteSize()];
		}

		Bitmap &Bitmap::operator=(Bitmap const& bitmap)
		{
			if(&bitmap == this)
				return *this;
			bool needs_realloc = getByteSize() < bitmap.getByteSize();
			if(pixels && needs_realloc)
			{
				delete[] pixels;
				pixels = nullptr;
			}

			channel = bitmap.channel;
			width = bitmap.width;
			height = bitmap.height;

			size_t size = getByteSize();
			if(!pixels || needs_realloc)
				pixels = new byte[size];

			memcpy(pixels, bitmap.pixels, size);

			return *this;
		}

		Bitmap &Bitmap::operator=(Bitmap && move)
		{
			if(&move == this)
				return *this;

			if(pixels)
		}

		uint32 Bitmap::getWidth() const
		{
			return width;
		}

		uint32 Bitmap::getHeight() const
		{
			return height;
		}

		ColorChannel Bitmap::getChannel() const
		{
			return channel;
		}

		size_t Bitmap::getByteSize() const
		{
			size_t size = width * height;

			switch(channel)
			{
			case ColorChannel::FLOAT1:
				{
					size *= sizeof(float);
				} break;
			case ColorChannel::FLOAT2:
				{
					size *= sizeof(math::fvec2);
				} break;
			case ColorChannel::FLOAT3:
				{
					size *= sizeof(math::fvec3);
				} break;
			case ColorChannel::FLOAT4:
				{
					size *= sizeof(math::fvec4);
				} break;
			case ColorChannel::BYTE1:
				{
					size *= sizeof(byte);
				} break;
			case ColorChannel::BYTE2:
				{
					size *= sizeof(math::vec2<byte>);
				} break;
			case ColorChannel::BYTE3:
				{
					size *= sizeof(math::vec3<byte>);
				} break;
			case ColorChannel::BYTE4:
				{
					size *= sizeof(math::vec4<byte>);
				} break;
			}

			return size;
		}

		void* Bitmap::getBaseAddress()
		{
			return pixels;
		}

		const void* Bitmap::getBaseAddress() const
		{
			return pixels;
		}

		float &Bitmap::getFloat1(uint32 x, uint32 y)
		{
			RE_ASSERT(x<width && y<height && channel==ColorChannel::FLOAT1);

			return static_cast<float*>(pixels)[x+y*width];
		}

		math::vec2<float> &Bitmap::getFloat2(uint32 x, uint32 y)
		{
			RE_ASSERT(x<width && y<height && channel==ColorChannel::FLOAT2);

			return static_cast<math::vec2<float>*>(pixels)[x+y*width];
		}

		math::vec3<float> &Bitmap::getFloat3(uint32 x, uint32 y)
		{
			RE_ASSERT(x<width && y<height && channel==ColorChannel::FLOAT3);

			return static_cast<math::vec3<float>*>(pixels)[x+y*width];
		}

		math::vec4<float> &Bitmap::getFloat4(uint32 x, uint32 y)
		{
			RE_ASSERT(x<width && y<height && channel==ColorChannel::FLOAT4);

			return static_cast<math::vec4<float>*>(pixels)[x+y*width];
		}

		ubyte &Bitmap::getByte1(uint32 x, uint32 y)
		{
			RE_ASSERT(x<width && y<height && channel==ColorChannel::BYTE1);

			return static_cast<ubyte*>(pixels)[x+y*width];
		}

		math::vec2<ubyte> &Bitmap::getByte2(uint32 x, uint32 y)
		{
			RE_ASSERT(x<width && y<height && channel==ColorChannel::BYTE2);

			return static_cast<math::vec2<ubyte>*>(pixels)[x+y*width];
		}

		math::vec3<ubyte> &Bitmap::getByte3(uint32 x, uint32 y)
		{
			RE_ASSERT(x<width && y<height && channel==ColorChannel::BYTE3);

			return static_cast<math::vec3<ubyte>*>(pixels)[x+y*width];
		}

		math::vec4<ubyte> &Bitmap::getByte4(uint32 x, uint32 y)
		{
			RE_ASSERT(x<width && y<height && channel==ColorChannel::BYTE4);
			
			return static_cast<math::vec4<ubyte>*>(pixels)[x+y*width];
		}

		const float &Bitmap::getFloat1(uint32 x, uint32 y) const
		{
			RE_ASSERT(x<width && y<height && channel==ColorChannel::FLOAT1);

			return static_cast<float*>(pixels)[x+y*width];
		}

		const math::vec2<float> &Bitmap::getFloat2(uint32 x, uint32 y) const
		{
			RE_ASSERT(x<width && y<height && channel==ColorChannel::FLOAT2);

			return static_cast<math::vec2<float>*>(pixels)[x+y*width];
		}

		const math::vec3<float> &Bitmap::getFloat3(uint32 x, uint32 y) const
		{
			RE_ASSERT(x<width && y<height && channel==ColorChannel::FLOAT3);

			return static_cast<math::vec3<float>*>(pixels)[x+y*width];
		}

		const math::vec4<float> &Bitmap::getFloat4(uint32 x, uint32 y) const
		{
			RE_ASSERT(x<width && y<height && channel==ColorChannel::FLOAT4);

			return static_cast<math::vec4<float>*>(pixels)[x+y*width];
		}

		const ubyte &Bitmap::getByte1(uint32 x, uint32 y) const
		{
			RE_ASSERT(x<width && y<height && channel==ColorChannel::BYTE1);

			return static_cast<ubyte*>(pixels)[x+y*width];
		}

		const math::vec2<ubyte> &Bitmap::getByte2(uint32 x, uint32 y) const
		{
			RE_ASSERT(x<width && y<height && channel==ColorChannel::BYTE2);

			return static_cast<math::vec2<ubyte>*>(pixels)[x+y*width];
		}

		const math::vec3<ubyte> &Bitmap::getByte3(uint32 x, uint32 y) const
		{
			RE_ASSERT(x<width && y<height && channel==ColorChannel::BYTE3);

			return static_cast<math::vec3<ubyte>*>(pixels)[x+y*width];
		}

		const math::vec4<ubyte> &Bitmap::getByte4(uint32 x, uint32 y) const
		{
			RE_ASSERT(x<width && y<height && channel==ColorChannel::BYTE4);
			
			return static_cast<math::vec4<ubyte>*>(pixels)[x+y*width];
		}

		Bitmap Bitmap::generateMipMap(MipmapFilter filter) const
		{
			Bitmap mip(channel, width>>1, height>>1);

			switch(filter)
			{
			case MipmapFilter::Center:
				{
					switch(channel)
					{
					case ColorChannel::BYTE1:
						{
							for(uint x = 0; x < mip.width; x++)
								for(uint y = 0; y < mip.height; y++)
									mip.getByte1(x,y) = getByte1(x<<1, y<<1);
						} break;
					case ColorChannel::BYTE2:
						{
							for(uint x = 0; x < mip.width; x++)
								for(uint y = 0; y < mip.height; y++)
									mip.getByte2(x,y) = getByte2(x<<1,y<<1);
						} break;
					case ColorChannel::BYTE3:
						{
							for(uint x = 0; x < mip.width; x++)
								for(uint y = 0; y < mip.height; y++)
									mip.getByte3(x,y) = getByte3(x<<1,y<<1);
						} break;
					case ColorChannel::BYTE4:
						{
							for(uint x = 0; x < mip.width; x++)
								for(uint y = 0; y < mip.height; y++)
									mip.getByte4(x,y) = getByte4(x<<1,y<<1);
						} break;
					case ColorChannel::FLOAT1:
						{
							for(uint x = 0; x < mip.width; x++)
								for(uint y = 0; y < mip.height; y++)
									mip.getFloat1(x,y) = getFloat1(x<<1,y<<1);
						} break;
					case ColorChannel::FLOAT2:
						{
							for(uint x = 0; x < mip.width; x++)
								for(uint y = 0; y < mip.height; y++)
									mip.getFloat2(x,y) = getFloat2(x<<1,y<<1);
						} break;
					case ColorChannel::FLOAT3:
						{
							for(uint x = 0; x < mip.width; x++)
								for(uint y = 0; y < mip.height; y++)
									mip.getFloat3(x,y) = getFloat3(x<<1,y<<1);
						} break;
					case ColorChannel::FLOAT4:
						{
							for(uint x = 0; x < mip.width; x++)
								for(uint y = 0; y < mip.height; y++)
									mip.getFloat4(x,y) = getFloat4(x<<1,y<<1);
						} break;
					}
				} break;
			case MipmapFilter::Adjacent4:
				{
					switch(channel)
					{
					case ColorChannel::BYTE1:
						{
							uword sum;
							ubyte v[5];
							for(uint x = 0; x < mip.width; x++)
							{
								const uint t_x = x+x;
								for(uint y = 0; y < mip.height; y++)
								{
									const uint t_y = y+y;
									v[2] = getByte1(t_x, t_y);
									// left column
									if(x != 0)
										v[0] = getByte1(t_x-1, t_y);
									else
										v[0] = v[2];

									// middle column
									if(y != 0)
										v[1] = getByte1(t_x, t_y-1);
									else
										v[1] = v[2];


									if(y+1 < mip.height)
										v[3] = getByte1(t_x, t_y+1);
									else
										v[3] = v[2];

									// right column
									if(x+1 < mip.width)
										v[4] = getByte1(t_x+1, t_y);
									else
										v[4] = v[2];

									sum = 0;
									for(auto val : v)
										sum = sum + val;
									sum = sum / 5;
									mip.getByte1(x,y) = byte(sum);
								}
							}
						} break;
					case ColorChannel::BYTE2:
						{
							math::vec2<uword> sum;
							math::vec2<ubyte> v[5];
							for(uint x = 0; x < mip.width; x++)
							{
								const uint t_x = x+x;
								for(uint y = 0; y < mip.height; y++)
								{
									const uint t_y = y+y;
									v[2] = getByte2(t_x, t_y);
									// left column
									if(x != 0)
										v[0] = getByte2(t_x-1, t_y);
									else
										v[0] = v[2];

									// middle column
									if(y != 0)
										v[1] = getByte2(t_x, t_y-1);
									else
										v[1] = v[2];


									if(y+1 < mip.height)
										v[3] = getByte2(t_x, t_y+1);
									else
										v[3] = v[2];

									// right column
									if(x+1 < mip.width)
										v[4] = getByte2(t_x+1, t_y);
									else
										v[4] = v[2];

									sum = decltype(sum)();
									for(auto val : v)
										sum = sum + decltype(sum)(val);
									sum = sum / 5;
									mip.getByte2(x,y) = math::vec2<ubyte>(sum);
								}
							}
						} break;
					case ColorChannel::BYTE3:
						{
							math::vec3<uword> sum;
							math::vec3<ubyte> v[5];
							for(uint x = 0; x < mip.width; x++)
							{
								const uint t_x = x+x;
								for(uint y = 0; y < mip.height; y++)
								{
									const uint t_y = y+y;
									v[2] = getByte3(t_x, t_y);
									// left column
									if(x != 0)
										v[0] = getByte3(t_x-1, t_y);
									else
										v[0] = v[2];

									// middle column
									if(y != 0)
										v[1] = getByte3(t_x, t_y-1);
									else
										v[1] = v[2];


									if(y+1 < mip.height)
										v[3] = getByte3(t_x, t_y+1);
									else
										v[3] = v[2];

									// right column
									if(x+1 < mip.width)
										v[4] = getByte3(t_x+1, t_y);
									else
										v[4] = v[2];

									sum = decltype(sum)();
									for(auto val : v)
										sum = sum + decltype(sum)(val);
									sum = sum / 5;
									mip.getByte3(x,y) = math::vec3<ubyte>(sum);
								}
							}
						} break;
					case ColorChannel::BYTE4:
						{
							math::vec4<uword> sum;
							math::vec4<ubyte> v[5];
							for(uint x = 0; x < mip.width; x++)
							{
								const uint t_x = x+x;
								for(uint y = 0; y < mip.height; y++)
								{
									const uint t_y = y+y;
									v[2] = getByte4(t_x, t_y);
									// left column
									if(x != 0)
										v[0] = getByte4(t_x-1, t_y);
									else
										v[0] = v[2];

									// middle column
									if(y != 0)
										v[1] = getByte4(t_x, t_y-1);
									else
										v[1] = v[2];


									if(y+1 < mip.height)
										v[3] = getByte4(t_x, t_y+1);
									else
										v[3] = v[2];

									// right column
									if(x+1 < mip.width)
										v[4] = getByte4(t_x+1, t_y);
									else
										v[4] = v[2];

									sum = decltype(sum)();
									for(auto val : v)
										sum = sum + decltype(sum)(val);
									sum = sum / 5;
									mip.getByte4(x,y) = math::vec4<ubyte>(sum);
								}
							}
						} break;
					case ColorChannel::FLOAT1:
						{
							float sum;
							float v[5];
							for(uint x = 0; x < mip.width; x++)
							{
								const uint t_x = x+x;
								for(uint y = 0; y < mip.height; y++)
								{
									const uint t_y = y+y;
									v[2] = getFloat1(t_x, t_y);
									for(float&_:v)_=v[2];
									// left column
									if(x != 0)
										v[0] = getFloat1(t_x-1, t_y);

									// middle column
									if(y != 0)
										v[1] = getFloat1(t_x, t_y-1);


									if(y+1 < mip.height)
										v[3] = getFloat1(t_x, t_y+1);

									// right column
									if(x+1 < mip.width)
										v[4] = getFloat1(t_x+1, t_y);

									sum = decltype(sum)();

									for(auto val : v)
										sum = sum + (val);
									sum = sum / 5;
									mip.getFloat1(x,y) = sum;
								}
							}
						} break;
					case ColorChannel::FLOAT2:
						{
							math::fvec2 sum;
							math::fvec2 v[5];
							for(uint x = 0; x < mip.width; x++)
							{
								const uint t_x = x+x;
								for(uint y = 0; y < mip.height; y++)
								{
									const uint t_y = y+y;
									v[2] = getFloat2(t_x, t_y);
									for(auto&_:v)_=v[2];
									// left column
									if(x != 0)
										v[0] = getFloat2(t_x-1, t_y);

									// middle column
									if(y != 0)
										v[1] = getFloat2(t_x, t_y-1);


									if(y+1 < mip.height)
										v[3] = getFloat2(t_x, t_y+1);

									// right column
									if(x+1 < mip.width)
										v[4] = getFloat2(t_x+1, t_y);

									sum = decltype(sum)();

									for(auto val : v)
										sum = sum + (val);
									sum = sum / 5;
									mip.getFloat2(x,y) = (sum);
								}
							}
						} break;
					case ColorChannel::FLOAT3:
						{
							math::fvec3 sum;
							math::fvec3 v[5];
							for(uint x = 0; x < mip.width; x++)
							{
								const uint t_x = x+x;
								for(uint y = 0; y < mip.height; y++)
								{
									const uint t_y = y+y;
									v[2] = getFloat3(t_x, t_y);
									for(auto&_:v)_=v[2];
									// left column
									if(x != 0)
										v[0] = getFloat3(t_x-1, t_y);

									// middle column
									if(y != 0)
										v[1] = getFloat3(t_x, t_y-1);


									if(y+1 < mip.height)
										v[3] = getFloat3(t_x, t_y+1);

									// right column
									if(x+1 < mip.width)
										v[4] = getFloat3(t_x+1, t_y);

									sum = decltype(sum)();

									for(auto val : v)
										sum = sum + (val);
									sum = sum / 5;
									mip.getFloat3(x,y) = (sum);
								}
							}
						} break;
					case ColorChannel::FLOAT4:
						{
							math::fvec4 sum;
							math::fvec4 v[5];
							for(uint x = 0; x < mip.width; x++)
							{
								const uint t_x = x+x;
								for(uint y = 0; y < mip.height; y++)
								{
									const uint t_y = y+y;
									v[2] = getFloat4(t_x, t_y);
									for(auto&_:v)_=v[2];
									// left column
									if(x != 0)
										v[0] = getFloat4(t_x-1, t_y);

									// middle column
									if(y != 0)
										v[1] = getFloat4(t_x, t_y-1);


									if(y+1 < mip.height)
										v[3] = getFloat4(t_x, t_y+1);

									// right column
									if(x+1 < mip.width)
										v[4] = getFloat4(t_x+1, t_y);

									sum = decltype(sum)();

									for(auto val : v)
										sum = sum + (val);
									sum = sum / 5;
									mip.getFloat4(x,y) = (sum);
								}
							}
						} break;
					}
				} break;
			case MipmapFilter::Adjacent8:
				{
					switch(channel)
					{
					case ColorChannel::BYTE1:
						{
							uword sum;
							ubyte v[3*3];
							for(uint x = 0; x < mip.width; x++)
							{
								const uint t_x = x+x;
								for(uint y = 0; y < mip.height; y++)
								{
									const uint t_y = y+y;
									v[4] = getByte1(t_x, t_y);
									for(auto&_:v)_=v[4];
									// left column
									if(x != 0)
									{
										if(y != 0)
											v[0] = getByte1(t_x-1,t_y-1);
										v[3] = getByte1(t_x-1, t_y);
										if(y+1 < mip.height)
											v[6] = getByte1(t_x-1, t_y+1);
									}
									// middle column
									if(y != 0)
										v[1] = getByte1(t_x, t_y-1);
									if(y+1 < mip.height)
										v[7] = getByte1(t_x, t_y+1);
									// right column
									if(x+1 < mip.width)
									{
										if(y != 0)
											v[2] = getByte1(t_x+1, t_y-1);
										v[5] = getByte1(t_x+1, t_y);
										if(y+1 < mip.height)
											v[6] = getByte1(t_x+1, t_y+1);
									}
									sum = 0;
									for(auto val : v)
										sum = sum + val;
									sum = sum / 9;
									mip.getByte1(x,y) = byte(sum);
								}

							}
						} break;
						case ColorChannel::BYTE2:
						{
							math::vec2<uword> sum;
							math::vec2<ubyte> v[3*3];
							for(uint x = 0; x < mip.width; x++)
							{
								const uint t_x = x+x;
								for(uint y = 0; y < mip.height; y++)
								{
									const uint t_y = y+y;
									v[4] = getByte2(t_x, t_y);
									for(auto&_:v)_=v[4];
									// left column
									if(x != 0)
									{
										if(y != 0)
											v[0] = getByte2(t_x-1,t_y-1);
										v[3] = getByte2(t_x-1, t_y);
										if(y+1 < mip.height)
											v[6] = getByte2(t_x-1, t_y+1);
									}
									// middle column
									if(y != 0)
										v[1] = getByte2(t_x, t_y-1);
									if(y+1 < mip.height)
										v[7] = getByte2(t_x, t_y+1);
									// right column
									if(x+1 < mip.width)
									{
										if(y != 0)
											v[2] = getByte2(t_x+1, t_y-1);
										v[5] = getByte2(t_x+1, t_y);
										if(y+1 < mip.height)
											v[6] = getByte2(t_x+1, t_y+1);
									}
									sum = math::vec2<uword>();
									for(auto val : v)
										sum = sum + math::vec2<uword>(val);
									sum = sum / 9;
									mip.getByte2(x,y) = math::vec2<ubyte>(sum);
								}

							}
						} break;
						case ColorChannel::BYTE3:
						{
							math::vec3<uword> sum;
							math::vec3<ubyte> v[3*3];
							for(uint x = 0; x < mip.width; x++)
							{
								const uint t_x = x+x;
								for(uint y = 0; y < mip.height; y++)
								{
									const uint t_y = y+y;
									v[4] = getByte3(t_x, t_y);
									for(auto&_:v)_=v[4];
									// left column
									if(x != 0)
									{
										if(y != 0)
											v[0] = getByte3(t_x-1,t_y-1);
										v[3] = getByte3(t_x-1, t_y);
										if(y+1 < mip.height)
											v[6] = getByte3(t_x-1, t_y+1);
									}
									// middle column
									if(y != 0)
										v[1] = getByte3(t_x, t_y-1);
									if(y+1 < mip.height)
										v[7] = getByte3(t_x, t_y+1);
									// right column
									if(x+1 < mip.width)
									{
										if(y != 0)
											v[2] = getByte3(t_x+1, t_y-1);
										v[5] = getByte3(t_x+1, t_y);
										if(y+1 < mip.height)
											v[6] = getByte3(t_x+1, t_y+1);
									}
									sum = math::vec3<uword>();
									for(auto val : v)
										sum = sum + math::vec3<uword>(val);
									sum = sum / 9;
									mip.getByte3(x,y) = math::vec3<ubyte>(sum);
								}

							}
						} break;
						case ColorChannel::BYTE4:
						{
							math::vec4<uword> sum;
							math::vec4<ubyte> v[3*3];
							for(uint x = 0; x < mip.width; x++)
							{
								const uint t_x = x+x;
								for(uint y = 0; y < mip.height; y++)
								{
									const uint t_y = y+y;
									v[4] = getByte4(t_x, t_y);
									for(auto&_:v)_=v[4];
									// left column
									if(x != 0)
									{
										if(y != 0)
											v[0] = getByte4(t_x-1,t_y-1);
										v[3] = getByte4(t_x-1, t_y);
										if(y+1 < mip.height)
											v[6] = getByte4(t_x-1, t_y+1);
									}
									// middle column
									if(y != 0)
										v[1] = getByte4(t_x, t_y-1);
									if(y+1 < mip.height)
										v[7] = getByte4(t_x, t_y+1);
									// right column
									if(x+1 < mip.width)
									{
										if(y != 0)
											v[2] = getByte4(t_x+1, t_y-1);
										v[5] = getByte4(t_x+1, t_y);
										if(y+1 < mip.height)
											v[6] = getByte4(t_x+1, t_y+1);
									}
									sum = math::vec4<uword>();
									for(auto val : v)
										sum = sum + math::vec4<uword>(val);
									sum = sum / 9;
									mip.getByte4(x,y) = math::vec4<ubyte>(sum);
								}

							}
						} break;
						case ColorChannel::FLOAT1:
						{
							float sum;
							float v[3*3];
							for(uint x = 0; x < mip.width; x++)
							{
								const uint t_x = x+x;
								for(uint y = 0; y < mip.height; y++)
								{
									const uint t_y = y+y;
									v[4] = getFloat1(t_x, t_y);
									for(auto&_:v)_=v[4];
									// left column
									if(x != 0)
									{
										if(y != 0)
											v[0] = getFloat1(t_x-1,t_y-1);
										v[3] = getFloat1(t_x-1, t_y);
										if(y+1 < mip.height)
											v[6] = getFloat1(t_x-1, t_y+1);
									}
									// middle column
									if(y != 0)
										v[1] = getFloat1(t_x, t_y-1);
									if(y+1 < mip.height)
										v[7] = getFloat1(t_x, t_y+1);
									// right column
									if(x+1 < mip.width)
									{
										if(y != 0)
											v[2] = getFloat1(t_x+1, t_y-1);
										v[5] = getFloat1(t_x+1, t_y);
										if(y+1 < mip.height)
											v[6] = getFloat1(t_x+1, t_y+1);
									}
									sum = 0;
									for(auto val : v)
										sum = sum + val;
									sum = sum / 9;
									mip.getFloat1(x,y) = sum;
								}

							}
						} break;
						case ColorChannel::FLOAT2:
						{
							math::vec2<float> sum;
							math::vec2<float> v[3*3];
							for(uint x = 0; x < mip.width; x++)
							{
								const uint t_x = x+x;
								for(uint y = 0; y < mip.height; y++)
								{
									const uint t_y = y+y;
									v[4] = getFloat2(t_x, t_y);
									for(auto&_:v)_=v[4];
									// left column
									if(x != 0)
									{
										if(y != 0)
											v[0] = getFloat2(t_x-1,t_y-1);
										v[3] = getFloat2(t_x-1, t_y);
										if(y+1 < mip.height)
											v[6] = getFloat2(t_x-1, t_y+1);
									}
									// middle column
									if(y != 0)
										v[1] = getFloat2(t_x, t_y-1);
									if(y+1 < mip.height)
										v[7] = getFloat2(t_x, t_y+1);
									// right column
									if(x+1 < mip.width)
									{
										if(y != 0)
											v[2] = getFloat2(t_x+1, t_y-1);
										v[5] = getFloat2(t_x+1, t_y);
										if(y+1 < mip.height)
											v[6] = getFloat2(t_x+1, t_y+1);
									}
									sum = math::vec2<float>();
									for(auto val : v)
										sum = sum + math::vec2<float>(val);
									sum = sum / 9;
									mip.getFloat2(x,y) = sum;
								}

							}
						} break;
						case ColorChannel::FLOAT3:
						{
							math::vec3<float> sum;
							math::vec3<float> v[3*3];
							for(uint x = 0; x < mip.width; x++)
							{
								const uint t_x = x+x;
								for(uint y = 0; y < mip.height; y++)
								{
									const uint t_y = y+y;
									v[4] = getFloat3(t_x, t_y);
									for(auto&_:v)_=v[4];
									// left column
									if(x != 0)
									{
										if(y != 0)
											v[0] = getFloat3(t_x-1,t_y-1);
										v[3] = getFloat3(t_x-1, t_y);
										if(y+1 < mip.height)
											v[6] = getFloat3(t_x-1, t_y+1);
									}
									// middle column
									if(y != 0)
										v[1] = getFloat3(t_x, t_y-1);
									if(y+1 < mip.height)
										v[7] = getFloat3(t_x, t_y+1);
									// right column
									if(x+1 < mip.width)
									{
										if(y != 0)
											v[2] = getFloat3(t_x+1, t_y-1);
										v[5] = getFloat3(t_x+1, t_y);
										if(y+1 < mip.height)
											v[6] = getFloat3(t_x+1, t_y+1);
									}
									sum = math::vec3<float>();
									for(auto val : v)
										sum = sum + math::vec3<float>(val);
									sum = sum / 9;
									mip.getFloat3(x,y) = sum;
								}

							}
						} break;
						case ColorChannel::FLOAT4:
						{
							math::vec4<float> sum;
							math::vec4<float> v[3*3];
							for(uint x = 0; x < mip.width; x++)
							{
								const uint t_x = x+x;
								for(uint y = 0; y < mip.height; y++)
								{
									const uint t_y = y+y;
									v[4] = getFloat4(t_x, t_y);
									for(auto&_:v)_=v[4];
									// left column
									if(x != 0)
									{
										if(y != 0)
											v[0] = getFloat4(t_x-1,t_y-1);
										v[3] = getFloat4(t_x-1, t_y);
										if(y+1 < mip.height)
											v[6] = getFloat4(t_x-1, t_y+1);
									}
									// middle column
									if(y != 0)
										v[1] = getFloat4(t_x, t_y-1);
									if(y+1 < mip.height)
										v[7] = getFloat4(t_x, t_y+1);
									// right column
									if(x+1 < mip.width)
									{
										if(y != 0)
											v[2] = getFloat4(t_x+1, t_y-1);
										v[5] = getFloat4(t_x+1, t_y);
										if(y+1 < mip.height)
											v[6] = getFloat4(t_x+1, t_y+1);
									}
									sum = math::vec4<float>();
									for(auto val : v)
										sum = sum + math::vec4<float>(val);
									sum = sum / 9;
									mip.getFloat4(x,y) = sum;
								}

							}
						} break;
					}
				} break;
			}
			return mip;
		}
	}
}