#include "Bitmap.hpp"
#include <memory>

namespace re
{
	namespace graphics
	{
		Bitmap::Bitmap():
			m_size(0),
			m_data(0)
		{
		}

		Bitmap::Bitmap(Channel channel, Component component, uint32 size):
			m_channel(channel),
			m_component(component),
			m_size(0),
			m_data(nullptr)
		{
			alloc(channel, component, size);
		}

		RECXDA size_of(Channel ch, Component c)
		{
			static int components const[] = { 1, 2, 3, 4 };
			static int size const[] = { sizeof(float), sizeof(ubyte) };
			
			RE_DBG_ASSERT(size_t(ch) < _countof(components));
			RE_DBG_ASSERT(size_t(c) < _countof(size));

			return components[ch] * size[c];
		}

		Bitmap::Bitmap(Bitmap const& copy):
			m_size(0),
			m_data(nullptr)
		{
			alloc(
				copy.m_channel,
				copy.m_component,
				copy.m_size);

			std::memcpy(
				m_data,
				copy.m_data,
				copy.m_size * size_of(m_channel, m_component));
		}

		Bitmap::Bitmap(Bitmap && move):
			m_channel(move.m_channel),
			m_component(move.m_component),
			m_size(move.m_size),
			m_data(move.m_data)
		{
			move.m_data = nullptr;
		}

		Bitmap &Bitmap::operator=(Bitmap const& copy)
		{
			RE_DBG_ASSERT(this != &copy);

			alloc(
				copy.m_channel,
				copy.m_component,
				copy.m_size);

			std::memcpy(
				m_data,
				copy.m_data,
				copy.m_size * size_of(m_channel, m_component));

			return *this;
		}

		Bitmap &Bitmap::operator=(Bitmap && move)
		{
			RE_DBG_ASSERT(this != &copy);

			if(exists())
				free();

			m_channel = move.m_channel;
			m_component = move.m_component;
			m_data = move.m_data;
			m_size = move.m_size;

			move.m_data = nullptr;
		}

		Bitmap::~Bitmap()
		{
			if(exists())
				free();
		}

		void Bitmap::alloc(
			Channel channel,
			Component component,
			uint32 size)
		{
			m_data = realloc(m_data, size * size_of(channel, component));
			m_size = size;
			m_channel = channel;
			m_component = component;
		}

		void Bitmap::free()
		{
			if(exists())
			{
				std::free(m_data);
				m_data = nullptr;
			}
		}

		Bitmap1D::Bitmap1D(Channel channel, Component component, uint32 size):
			Bitmap(channel, component, size)
		{
		}

		Bitmap2D::Bitmap2D(Channel channel, Component component, uint32 width, uint32 height):
			Bitmap(channel, component, width * height),
			m_width(width),
			m_height(height)
		{
			RE_DBG_ASSERT(width > 0);
			RE_DBG_ASSERT(height > 0);
		}

		Bitmap3D::Bitmap3D(
			Channel channel,
			Component component,
			uint32 width,
			uint32 height,
			uint32 depth):
			Bitmap(channel, component, width * height * depth),
			m_width(width),
			m_height(height),
			m_depth(depth)
		{
			RE_DBG_ASSERT(width > 0);
			RE_DBG_ASSERT(height > 0);
			RE_DBG_ASSERT(depth > 0);
		}

		Bitmap1D Bitmap1D::create_mipmap_near() const
		{
			RE_DBG_ASSERT(exists());
			RE_DBG_ASSERT(size() > 1);

			Bitmap1D mip(channel(), component(), size() >> 1);

			for(uint32 i = mip.size(); i--;)
				mip.pixel<ch,co>(i) = mip_near<ch,co>(i);

			return std::move(mip);
		}

		Bitmap1D Bitmap1D::create_mipmap_lin() const
		{
			RE_DBG_ASSERT(exists());
			RE_DBG_ASSERT(size() > 1);

			Bitmap1D mip(channel(), component(), size() >> 1);

			for(uint32 i = mip.size(); i--;)
				mip.pixel<ch,co>(i) = mip_lin<ch,co>(i);

			return std::move(mip);
		}

		Bitmap2D Bitmap2D::create_mipmap_near() const
		{
			RE_DBG_ASSERT(exists());
			RE_DBG_ASSERT(size() > 1);

			uint32 new_width = width() >> 1;
			if(!new_width)
				new_width = 1;
			uint32 new_height = height() >> 1;
			if(!new_height)
				new_height = 1;

			Bitmap2D mip(channel(), component(), new_width, new_height);

			for(uint32 x = mip.width(); x--;)
				for(uint32 y = mip.height(); y--;)
					mip.pixel<ch,co>(x,y) = mip_near<ch,co>(x,y);
		}

		Bitmap2D Bitmap2D::create_mipmap_near() const
		{
			RE_DBG_ASSERT(exists());
			RE_DBG_ASSERT(size() > 1);

			uint32 new_width = width() >> 1;
			if(!new_width)
				new_width = 1;
			uint32 new_height = height() >> 1;
			if(!new_height)
				new_height = 1;

			Bitmap2D mip(channel(), component(), new_width, new_height);

			for(uint32 x = mip.width(); x--;)
				for(uint32 y = mip.height(); y--;)
					mip.pixel<ch,co>(x,y) = mip_lin<ch,co>(x,y);

			return std::move(mip);
		}

		Bitmap3D Bitmap3D::create_mipmap_near() const
		{
			RE_DBG_ASSERT(exists());
			RE_DBG_ASSERT(size() > 1);

			uint32 new_width = width() >> 1;
			if(!new_width)
				new_width = 1;
			uint32 new_height = height() >> 1;
			if(!new_height)
				new_height = 1;
			uint32 new_depth = depth() >> 1;
			if(!new_depth)
				new_depth = 1;

			Bitmap3D mip(channel(), component(), new_width, new_height, new_depth);

			for(uint32 x = mip.width(); x--;)
				for(uint32 y = mip.height(); y--;)
					for(uint32 z = mip.depth(); z--;)
						mip.pixel<ch,co>(x,y,z) = mip_near<ch,co>(x,y,z);

			return std::move(mip);
		}

		Bitmap3D Bitmap3D::create_mipmap_near() const
		{
			RE_DBG_ASSERT(exists());
			RE_DBG_ASSERT(size() > 1);

			uint32 new_width = width() >> 1;
			if(!new_width)
				new_width = 1;
			uint32 new_height = height() >> 1;
			if(!new_height)
				new_height = 1;
			uint32 new_depth = depth() >> 1;
			if(!new_depth)
				new_depth = 1;

			Bitmap3D mip(channel(), component(), new_width, new_height, new_depth);

			for(uint32 x = mip.width(); x--;)
				for(uint32 y = mip.height(); y--;)
					for(uint32 z = mip.depth(); z--;)
						mip.pixel<ch,co>(x,y,z) = mip_lin<ch,co>(x,y,z);

			return std::move(mip);
		}
		
	}
}