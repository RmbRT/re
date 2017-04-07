#include "Bitmap.hpp"
#include <memory>
#include <cstring>

#include "../math/MathUtil.hpp"

namespace re
{
	namespace graphics
	{
		Bitmap::Bitmap(Channel channel, Component component, uint32_t size):
			m_channel(channel),
			m_component(component),
			m_size(0),
			m_data(nullptr)
		{
			alloc(channel, component, size);
		}

		size_t size_of(Channel ch, Component c)
		{
			static int const components[] = { 1, 2, 3, 4 };
			static int const size[] = { sizeof(float), sizeof(ubyte_t) };

			RE_DBG_ASSERT(size_t(ch) < _countof(components));
			RE_DBG_ASSERT(size_t(c) < _countof(size));

			return components[size_t(ch)] * size[size_t(c)];
		}

		size_t Bitmap::byte_size() const
		{
			return size_of(m_channel, m_component) * m_size;
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
			uint32_t size)
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

		Bitmap1D::Bitmap1D(Channel channel, Component component, uint32_t size):
			Bitmap(channel, component, size)
		{
		}

		Bitmap2D::Bitmap2D(Channel channel, Component component, uint32_t width, uint32_t height):
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
			uint32_t width,
			uint32_t height,
			uint32_t depth):
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

			switch(channel())
			{
			case Channel::kR:
				{
					if(component() == Component::kFloat)
						for(uint32_t i = mip.size(); i--;)
							mip.pixel<Channel::kR,Component::kFloat>(i) = mip_near<Channel::kR,Component::kFloat>(i);
					else
						for(uint32_t i = mip.size(); i--;)
							mip.pixel<Channel::kR,Component::kUbyte>(i) = mip_near<Channel::kR,Component::kUbyte>(i);
				} break;
				case Channel::kRg:
				{
					if(component() == Component::kFloat)
						for(uint32_t i = mip.size(); i--;)
							mip.pixel<Channel::kRg,Component::kFloat>(i) = mip_near<Channel::kRg,Component::kFloat>(i);
					else
						for(uint32_t i = mip.size(); i--;)
							mip.pixel<Channel::kRg,Component::kUbyte>(i) = mip_near<Channel::kRg,Component::kUbyte>(i);
				} break;
				case Channel::kRgb:
				{
					if(component() == Component::kFloat)
						for(uint32_t i = mip.size(); i--;)
							mip.pixel<Channel::kRgb,Component::kFloat>(i) = mip_near<Channel::kRgb,Component::kFloat>(i);
					else
						for(uint32_t i = mip.size(); i--;)
							mip.pixel<Channel::kRgb,Component::kUbyte>(i) = mip_near<Channel::kRgb,Component::kUbyte>(i);
				} break;
				case Channel::kRgba:
				{
					if(component() == Component::kFloat)
						for(uint32_t i = mip.size(); i--;)
							mip.pixel<Channel::kRgba,Component::kFloat>(i) = mip_near<Channel::kRgba,Component::kFloat>(i);
					else
						for(uint32_t i = mip.size(); i--;)
							mip.pixel<Channel::kRgba,Component::kUbyte>(i) = mip_near<Channel::kRgba,Component::kUbyte>(i);
				} break;
			}


			return std::move(mip);
		}

		Bitmap1D Bitmap1D::create_mipmap_lin() const
		{
			RE_DBG_ASSERT(exists());
			RE_DBG_ASSERT(size() > 1);

			Bitmap1D mip(channel(), component(), size() >> 1);
			switch(channel())
			{
			case Channel::kR:
				{
					if(component() == Component::kFloat)
						for(uint32_t i = mip.size(); i--;)
							mip.pixel<Channel::kR,Component::kFloat>(i) = mip_lin<Channel::kR,Component::kFloat>(i);
					else
						for(uint32_t i = mip.size(); i--;)
							mip.pixel<Channel::kR,Component::kUbyte>(i) = mip_lin<Channel::kR,Component::kUbyte>(i);
				} break;
				case Channel::kRg:
				{
					if(component() == Component::kFloat)
						for(uint32_t i = mip.size(); i--;)
							mip.pixel<Channel::kRg,Component::kFloat>(i) = mip_lin<Channel::kRg,Component::kFloat>(i);
					else
						for(uint32_t i = mip.size(); i--;)
							mip.pixel<Channel::kRg,Component::kUbyte>(i) = mip_lin<Channel::kRg,Component::kUbyte>(i);
				} break;
				case Channel::kRgb:
				{
					if(component() == Component::kFloat)
						for(uint32_t i = mip.size(); i--;)
							mip.pixel<Channel::kRgb,Component::kFloat>(i) = mip_lin<Channel::kRgb,Component::kFloat>(i);
					else
						for(uint32_t i = mip.size(); i--;)
							mip.pixel<Channel::kRgb,Component::kUbyte>(i) = mip_lin<Channel::kRgb,Component::kUbyte>(i);
				} break;
				case Channel::kRgba:
				{
					if(component() == Component::kFloat)
						for(uint32_t i = mip.size(); i--;)
							mip.pixel<Channel::kRgba,Component::kFloat>(i) = mip_lin<Channel::kRgba,Component::kFloat>(i);
					else
						for(uint32_t i = mip.size(); i--;)
							mip.pixel<Channel::kRgba,Component::kUbyte>(i) = mip_lin<Channel::kRgba,Component::kUbyte>(i);
				} break;
			}

			return std::move(mip);
		}

		Bitmap2D Bitmap2D::create_mipmap_lin() const
		{
			RE_DBG_ASSERT(exists());
			RE_DBG_ASSERT(size() > 1);

			uint32_t new_width = width() >> 1;
			if(!new_width)
				new_width = 1;
			uint32_t new_height = height() >> 1;
			if(!new_height)
				new_height = 1;

			Bitmap2D mip(channel(), component(), new_width, new_height);
			switch(channel())
			{
			case Channel::kR:
				{
					if(component() == Component::kFloat)
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								mip.pixel<Channel::kR,Component::kFloat>(x, y) = mip_lin<Channel::kR,Component::kFloat>(x, y);
					else
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								mip.pixel<Channel::kR,Component::kUbyte>(x, y) = mip_lin<Channel::kR,Component::kUbyte>(x, y);
				} break;
				case Channel::kRg:
				{
					if(component() == Component::kFloat)
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								mip.pixel<Channel::kRg,Component::kFloat>(x, y) = mip_lin<Channel::kRg,Component::kFloat>(x, y);
					else
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								mip.pixel<Channel::kRg,Component::kUbyte>(x, y) = mip_lin<Channel::kRg,Component::kUbyte>(x, y);
				} break;
				case Channel::kRgb:
				{
					if(component() == Component::kFloat)
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								mip.pixel<Channel::kRgb,Component::kFloat>(x, y) = mip_lin<Channel::kRgb,Component::kFloat>(x, y);
					else
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								mip.pixel<Channel::kRgb,Component::kUbyte>(x, y) = mip_lin<Channel::kRgb,Component::kUbyte>(x, y);
				} break;
				case Channel::kRgba:
				{
					if(component() == Component::kFloat)
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								mip.pixel<Channel::kRgba,Component::kFloat>(x, y) = mip_lin<Channel::kRgba,Component::kFloat>(x, y);
					else
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								mip.pixel<Channel::kRgba,Component::kUbyte>(x, y) = mip_lin<Channel::kRgba,Component::kUbyte>(x, y);
				} break;
			}

			return std::move(mip);
		}

		Bitmap2D Bitmap2D::create_mipmap_near() const
		{
			RE_DBG_ASSERT(exists());
			RE_DBG_ASSERT(size() > 1);

			uint32_t new_width = width() >> 1;
			if(!new_width)
				new_width = 1;
			uint32_t new_height = height() >> 1;
			if(!new_height)
				new_height = 1;

			Bitmap2D mip(channel(), component(), new_width, new_height);
			switch(channel())
			{
			case Channel::kR:
				{
					if(component() == Component::kFloat)
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								mip.pixel<Channel::kR,Component::kFloat>(x, y) = mip_near<Channel::kR,Component::kFloat>(x, y);
					else
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								mip.pixel<Channel::kR,Component::kUbyte>(x, y) = mip_near<Channel::kR,Component::kUbyte>(x, y);
				} break;
				case Channel::kRg:
				{
					if(component() == Component::kFloat)
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								mip.pixel<Channel::kRg,Component::kFloat>(x, y) = mip_near<Channel::kRg,Component::kFloat>(x, y);
					else
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								mip.pixel<Channel::kRg,Component::kUbyte>(x, y) = mip_near<Channel::kRg,Component::kUbyte>(x, y);
				} break;
				case Channel::kRgb:
				{
					if(component() == Component::kFloat)
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								mip.pixel<Channel::kRgb,Component::kFloat>(x, y) = mip_near<Channel::kRgb,Component::kFloat>(x, y);
					else
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								mip.pixel<Channel::kRgb,Component::kUbyte>(x, y) = mip_near<Channel::kRgb,Component::kUbyte>(x, y);
				} break;
				case Channel::kRgba:
				{
					if(component() == Component::kFloat)
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								mip.pixel<Channel::kRgba,Component::kFloat>(x, y) = mip_near<Channel::kRgba,Component::kFloat>(x, y);
					else
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								mip.pixel<Channel::kRgba,Component::kUbyte>(x, y) = mip_near<Channel::kRgba,Component::kUbyte>(x, y);
				} break;
			}

			return std::move(mip);
		}

		Bitmap3D Bitmap3D::create_mipmap_lin() const
		{
			RE_DBG_ASSERT(exists());
			RE_DBG_ASSERT(size() > 1);

			uint32_t new_width = width() >> 1;
			if(!new_width)
				new_width = 1;
			uint32_t new_height = height() >> 1;
			if(!new_height)
				new_height = 1;
			uint32_t new_depth = depth() >> 1;
			if(!new_depth)
				new_depth = 1;

			Bitmap3D mip(channel(), component(), new_width, new_height, new_depth);
			switch(channel())
			{
			case Channel::kR:
				{
					if(component() == Component::kFloat)
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								for(uint32_t z = mip.depth(); z--;)
									mip.pixel<Channel::kR,Component::kFloat>(x, y, z) = mip_lin<Channel::kR,Component::kFloat>(x, y, z);
					else
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								for(uint32_t z = mip.depth(); z--;)
									mip.pixel<Channel::kR,Component::kUbyte>(x, y, z) = mip_lin<Channel::kR,Component::kUbyte>(x, y, z);
				} break;
				case Channel::kRg:
				{
					if(component() == Component::kFloat)
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								for(uint32_t z = mip.depth(); z--;)
									mip.pixel<Channel::kRg,Component::kFloat>(x, y, z) = mip_lin<Channel::kRg,Component::kFloat>(x, y, z);
					else
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								for(uint32_t z = mip.depth(); z--;)
									mip.pixel<Channel::kRg,Component::kUbyte>(x, y, z) = mip_lin<Channel::kRg,Component::kUbyte>(x, y, z);
				} break;
				case Channel::kRgb:
				{
					if(component() == Component::kFloat)
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								for(uint32_t z = mip.depth(); z--;)
									mip.pixel<Channel::kRgb,Component::kFloat>(x, y, z) = mip_lin<Channel::kRgb,Component::kFloat>(x, y, z);
					else
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								for(uint32_t z = mip.depth(); z--;)
									mip.pixel<Channel::kRgb,Component::kUbyte>(x, y, z) = mip_lin<Channel::kRgb,Component::kUbyte>(x, y, z);
				} break;
				case Channel::kRgba:
				{
					if(component() == Component::kFloat)
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								for(uint32_t z = mip.depth(); z--;)
									mip.pixel<Channel::kRgba,Component::kFloat>(x, y, z) = mip_lin<Channel::kRgba,Component::kFloat>(x, y, z);
					else
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								for(uint32_t z = mip.depth(); z--;)
									mip.pixel<Channel::kRgba,Component::kUbyte>(x, y, z) = mip_lin<Channel::kRgba,Component::kUbyte>(x, y, z);
				} break;
			}

			return std::move(mip);
		}

		Bitmap3D Bitmap3D::create_mipmap_near() const
		{
			RE_DBG_ASSERT(exists());
			RE_DBG_ASSERT(size() > 1);

			uint32_t new_width = width() >> 1;
			if(!new_width)
				new_width = 1;
			uint32_t new_height = height() >> 1;
			if(!new_height)
				new_height = 1;
			uint32_t new_depth = depth() >> 1;
			if(!new_depth)
				new_depth = 1;

			Bitmap3D mip(channel(), component(), new_width, new_height, new_depth);

			switch(channel())
			{
			case Channel::kR:
				{
					if(component() == Component::kFloat)
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								for(uint32_t z = mip.depth(); z--;)
									mip.pixel<Channel::kR,Component::kFloat>(x, y, z) = mip_near<Channel::kR,Component::kFloat>(x, y, z);
					else
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								for(uint32_t z = mip.depth(); z--;)
									mip.pixel<Channel::kR,Component::kUbyte>(x, y, z) = mip_near<Channel::kR,Component::kUbyte>(x, y, z);
				} break;
				case Channel::kRg:
				{
					if(component() == Component::kFloat)
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								for(uint32_t z = mip.depth(); z--;)
									mip.pixel<Channel::kRg,Component::kFloat>(x, y, z) = mip_near<Channel::kRg,Component::kFloat>(x, y, z);
					else
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								for(uint32_t z = mip.depth(); z--;)
									mip.pixel<Channel::kRg,Component::kUbyte>(x, y, z) = mip_near<Channel::kRg,Component::kUbyte>(x, y, z);
				} break;
				case Channel::kRgb:
				{
					if(component() == Component::kFloat)
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								for(uint32_t z = mip.depth(); z--;)
									mip.pixel<Channel::kRgb,Component::kFloat>(x, y, z) = mip_near<Channel::kRgb,Component::kFloat>(x, y, z);
					else
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								for(uint32_t z = mip.depth(); z--;)
									mip.pixel<Channel::kRgb,Component::kUbyte>(x, y, z) = mip_near<Channel::kRgb,Component::kUbyte>(x, y, z);
				} break;
				case Channel::kRgba:
				{
					if(component() == Component::kFloat)
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								for(uint32_t z = mip.depth(); z--;)
									mip.pixel<Channel::kRgba,Component::kFloat>(x, y, z) = mip_near<Channel::kRgba,Component::kFloat>(x, y, z);
					else
						for(uint32_t x = mip.width(); x--;)
							for(uint32_t y = mip.height(); y--;)
								for(uint32_t z = mip.depth(); z--;)
									mip.pixel<Channel::kRgba,Component::kUbyte>(x, y, z) = mip_near<Channel::kRgba,Component::kUbyte>(x, y, z);
				} break;
			}

			return std::move(mip);
		}
		
	}
}