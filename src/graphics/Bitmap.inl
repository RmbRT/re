#include "../math/MathUtil.hpp"
namespace re
{
	namespace graphics
	{

		RECX Bitmap::Bitmap():
			m_size(0),
			m_data(0),
			m_component(),
			m_channel()
		{
		}

		bool Bitmap::exists() const
		{
			return m_data;
		}

		uint32_t Bitmap::size() const
		{
			RE_DBG_ASSERT(exists());
			return m_size;
		}

		Channel Bitmap::channel() const
		{
			RE_DBG_ASSERT(exists());
			return m_channel;
		}

		Component Bitmap::component() const
		{
			RE_DBG_ASSERT(exists());
			return m_component;
		}

		template<Channel kChannel, Component kComponent>
		pixel_t<kChannel,kComponent> & Bitmap::pixel(uint32_t index)
		{
			RE_DBG_ASSERT(exists());
			RE_DBG_ASSERT(index < m_size);
			RE_DBG_ASSERT(m_channel == kChannel);
			RE_DBG_ASSERT(m_component == kComponent);

			return static_cast<pixel_t<kChannel,kComponent> *>(m_data)[index];
		}

		template<Channel kChannel, Component kComponent>
		pixel_t<kChannel,kComponent> const& Bitmap::pixel(uint32_t index) const
		{
			RE_DBG_ASSERT(exists());
			RE_DBG_ASSERT(index < m_size);
			RE_DBG_ASSERT(m_channel == kChannel);
			RE_DBG_ASSERT(m_component == kComponent);

			return static_cast<pixel_t<kChannel,kComponent> const*>(m_data)[index];
		}

		void * Bitmap::data()
		{
			return m_data;
		}

		void const * Bitmap::data() const
		{
			return m_data;
		}

		RECX Bitmap1D::Bitmap1D():
			Bitmap()
		{
		}

		RECX Bitmap2D::Bitmap2D():
			Bitmap(),
			m_width(0),
			m_height(0)
		{
		}


		RECX Bitmap3D::Bitmap3D():
			Bitmap(),
			m_width(0),
			m_height(0),
			m_depth(0)
		{
		}

		template<Channel ch, Component co>
		pixel_t<ch,co> const& Bitmap1D::mip_near(uint32_t index) const
		{
			return pixel<ch,co>(index << 1);
		}

		template<Channel kChannel, Component kComponent>
		pixel_t<kChannel,kComponent> Bitmap1D::mip_lin(uint32_t index) const
		{
			index <<= 1;
			if(index+1 < size())
				return math::avg<pixel_t<kChannel, kComponent>, 2>({
					pixel<kChannel,kComponent>(index),
					pixel<kChannel,kComponent>(index+1)});
			else
				return mip_near<kChannel,kComponent>(index);
		}

		template<Channel kChannel, Component kComponent>
		pixel_t<kChannel,kComponent> & Bitmap2D::pixel(uint32_t x, uint32_t y)
		{
			RE_DBG_ASSERT(x < m_width);
			RE_DBG_ASSERT(y < m_height);

			return Bitmap::pixel<kChannel,kComponent>(x + y * m_width);
		}

		template<Channel ch, Component co>
		pixel_t<ch,co> const& Bitmap2D::pixel(uint32_t x, uint32_t y) const
		{
			RE_DBG_ASSERT(x < m_width);
			RE_DBG_ASSERT(y < m_height);

			return Bitmap::pixel<ch,co>(x + y * m_width);
		}

		void Bitmap2D::alloc(
			Channel channel,
			Component component,
			uint32_t width,
			uint32_t height)
		{
			static_cast<Bitmap*>(this)->alloc(
				channel,
				component,
				width * height);
		}

		uint32_t Bitmap2D::width() const
		{
			return m_width;
		}

		uint32_t Bitmap2D::height() const
		{
			return m_height;
		}

		template<Channel ch, Component co>
		pixel_t<ch,co> const& Bitmap2D::mip_near(uint32_t x, uint32_t y) const
		{
			return pixel<ch,co>(x<<1, y<<1);
		}

		template<Channel ch, Component co>
		pixel_t<ch,co> Bitmap2D::mip_lin(uint32_t x, uint32_t y) const
		{
			x <<= 1;
			y <<= 1;

			if(x + 1 < width())
				if(y + 1 < height())
					return math::avg<pixel_t<ch,co>, 4>({
						pixel<ch,co>(x, y),
						pixel<ch,co>(x+1, y),
						pixel<ch,co>(x, y+1),
						pixel<ch,co>(x+1, y+1)});
				else
					return math::avg<pixel_t<ch,co>, 2>({
						pixel<ch,co>(x, y),
						pixel<ch,co>(x+1, y)});
			else
				if(y + 1 < height())
					return math::avg<pixel_t<ch,co>, 2>({
						pixel<ch,co>(x, y),
						pixel<ch,co>(x, y+1)});
				else
					return pixel<ch,co>(x, y);
		}

		template<Channel ch, Component co>
		pixel_t<ch,co> & Bitmap3D::pixel(uint32_t x, uint32_t y, uint32_t z)
		{
			RE_DBG_ASSERT(x < width());
			RE_DBG_ASSERT(y < height());
			RE_DBG_ASSERT(z < depth());

			return Bitmap::pixel<ch,co>(x + (y + z * height()) * width());
		}

		template<Channel ch, Component co>
		pixel_t<ch,co> const& Bitmap3D::pixel(uint32_t x, uint32_t y, uint32_t z) const
		{
			RE_DBG_ASSERT(x < width());
			RE_DBG_ASSERT(y < height());
			RE_DBG_ASSERT(z < depth());

			return Bitmap::pixel<ch,co>(x + (y + z * height()) * width());
		}

		void Bitmap3D::alloc(
			Channel channel,
			Component component,
			uint32_t width,
			uint32_t height,
			uint32_t depth)
		{
			Bitmap::alloc(channel, component, width * height * depth);
		}

		uint32_t Bitmap3D::width() const
		{
			return m_width;
		}

		uint32_t Bitmap3D::height() const
		{
			return m_height;
		}

		uint32_t Bitmap3D::depth() const
		{
			return m_depth;
		}

		template<Channel ch, Component co>
		pixel_t<ch,co> const& Bitmap3D::mip_near(uint32_t x, uint32_t y, uint32_t z) const
		{
			return pixel<ch,co>(x<<1, y<<1, z<<1);
		}

		template<Channel ch, Component co>
		pixel_t<ch,co> Bitmap3D::mip_lin(uint32_t x, uint32_t y, uint32_t z) const
		{
			x <<= 1;
			y <<= 1;
			z <<= 1;

			if(x+1 < width())
				if(y+1 < height())
					if(z+1 < depth())
						return math::avg<pixel_t<ch,co>, 8>({
							pixel<ch,co>(x,   y,   z),
							pixel<ch,co>(x+1, y,   z),
							pixel<ch,co>(x,   y+1, z),
							pixel<ch,co>(x+1, y+1, z),
							pixel<ch,co>(x,   y,   z+1),
							pixel<ch,co>(x+1, y,   z+1),
							pixel<ch,co>(x,   y+1, z+1),
							pixel<ch,co>(x+1, y+1, z+1)});
					else
						return math::avg<pixel_t<ch,co>, 4>({
							pixel<ch,co>(x,   y,   z),
							pixel<ch,co>(x+1, y,   z),
							pixel<ch,co>(x,   y+1, z),
							pixel<ch,co>(x+1, y+1, z)});
				else
					if(z+1 < depth())
						return math::avg<pixel_t<ch,co>, 4>({
							pixel<ch,co>(x,   y,   z),
							pixel<ch,co>(x+1, y,   z),
							pixel<ch,co>(x,   y,   z+1),
							pixel<ch,co>(x+1, y,   z+1)});
					else
						return math::avg<pixel_t<ch,co>, 2>({
							pixel<ch,co>(x,   y,   z),
							pixel<ch,co>(x+1, y,   z)});
			else
				if(y+1 < height())
					if(z+1 < depth())
						return math::avg<pixel_t<ch,co>, 4>({
							pixel<ch,co>(x,   y,   z),
							pixel<ch,co>(x,   y+1, z),
							pixel<ch,co>(x,   y,   z+1),
							pixel<ch,co>(x,   y+1, z+1)});
					else
						return math::avg<pixel_t<ch,co>, 2>({
							pixel<ch,co>(x,   y,   z),
							pixel<ch,co>(x,   y+1, z)});
				else
					if(z+1 < depth())
						return math::avg<pixel_t<ch,co>, 2>({
							pixel<ch,co>(x,   y,   z),
							pixel<ch,co>(x,   y,   z+1)});
					else
						return
							pixel<ch,co>(x,   y,   z);
		}
	}
}