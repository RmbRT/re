#ifndef __re_graphics_bitmap_hpp_defined
#define __re_graphics_bitmap_hpp_defined

#include "../types.hpp"
#include "../defines.hpp"
#include "../math/Vector.hpp"

namespace re
{
	namespace graphics
	{
		/** Describes the color channels a Bitmap has. */
		enum class Channel
		{
			R,
			Rg,
			Rgb,
			Rgba
		};

		/** Describes the type of the color component a Bitmap has. */
		enum class Component
		{
			Float,
			Ubyte
		};

		namespace detail
		{
			template<Component c>
			struct ComponentType;

			template<>
			struct ComponentType<Component::Float> { typedef float type; };
			template<>
			struct ComponentType<Component::Ubyte> { typedef ubyte_t type; };

			template<Component T>
			using component_t = typename ComponentType<T>::type;

			template<Channel channel, Component comp>
			struct Pixel;

			template<Component comp>
			struct Pixel<Channel::R, comp> { typedef component_t<comp> type; };
			template<Component comp>
			struct Pixel<Channel::RG, comp> { typedef math::vec2<component_t<comp>> type; };
			template<Component comp>
			struct Pixel<Channel::RGB, comp> { typedef math::vec3<component_t<comp>> type; };
			template<Component comp>
			struct Pixel<Channel::RGBA, comp> { typedef math::vec4<component_t<comp>> type; };

		}

		template<Channel ch, Component co>
		using pixel_t = typename detail::Pixel<ch,co>::type;

		/** Represents an Image. */
		class Bitmap
		{
			Channel m_channel;
			Component m_component;
			/** The count of elements, not bytes. */
			uint32_t m_size;
			void* m_data;
		public:
			/** Constructs a non-allocated Bitmap. */
			Bitmap();
			/** Constructs an allocated Bitmap with he given Channel and Component and size.
			@param[in] channel:
				The number of channels the Bitmap should have.
			@param[in] component:
				The component type the Bitmap should have.
			@param[in] size:
				The pixel count the Bitmap should have. */
			Bitmap(Channel channel, Component component, uint32_t size);
			Bitmap(Bitmap const&);
			Bitmap(Bitmap &&);
			Bitmap &operator=(Bitmap const&);
			Bitmap &operator=(Bitmap &&);
			/** Frees the Bitmap if it was still allocated. */
			~Bitmap();

			/** Allocates the image data with the given channels and bounds. */
			void alloc(Channel channel, Component component, uint32_t size);
			/** Frees the image data. */
			void free();

			/** Returns whether the Bitmap contains image data. */
			RECX bool exists() const;
			/** Returns the pixel count of the Bitmap's image data, not the byte count.
			@assert The Bitmap must exist. */
			RECXDA uint32_t size() const;
			/** Returns the Channel of this Bitmap.
			@assert The Bitmap must exist. */
			RECXDA Channel channel() const;
			/** Returns the Component of this Bitmap.
			@assert The Bitmap must exist. */
			RECXDA Component component() const;

			/** Returns the pixel of the Bitmap at the given index.
			@assert The Bitmap must exist.
			@assert The Bitmap must have the identical Channel and Component.
			@assert index must be within the Bitmap's bounds. */
			template<Channel c, Component co>
			RECXDA14 pixel_t<c,co> & pixel(uint32_t index);
			/** Returns the pixel of the Bitmap at the given index.
			@assert The Bitmap must exist.
			@assert The Bitmap must have the identical Channel and Component.
			@assert index must be within the Bitmap's bounds. */
			template<Channel c, Component co>
			RECXDA pixel_t<c,co> const& pixel(uint32_t index) const;
		};

		/** Represents a one dimensional image. */
		class Bitmap1D : Bitmap
		{
		public:
			Bitmap1D() = default;
			/** @see Bitmap::Bitmap. */
			Bitmap1D(Channel channel, Component component, uint32_t size);

			using Bitmap::pixel;

			using Bitmap::exists;
			using Bitmap::size;
			using Bitmap::channel;
			using Bitmap::alloc;
			using Bitmap::free;

			/** Creates a mipmap using nearest filtering.
			@assert The Bitmap must exist.
			@assert The Bitmap must be larger than one pixel. */
			Bitmap1D create_mipmap_near() const;
			/** Creates a mipmap using linear filtering.
			@assert The Bitmap must exist.
			@assert The Bitmap must be larger than one pixel. */
			Bitmap1D create_mipmap_lin() const;

			/** Returns the mipmap's pixel at the given index using nearest filtering.
			@assert The index must be less than half the size of the Bitmap. */
			template<Channel ch, Component co>
			RECXDA pixel_t<ch,co> const& mip_near(uint32_t index) const;
			/** Returns the mipmap's pixel at the given index using linear filtering.
			@assert The index must be less than half the size of the Bitmap. */
			template<Channel ch, Component co>
			RECXDA pixel_t<ch,co> mip_lin(uint32_t index) const;
		};

		/** Represents a two dimensional image. */
		class Bitmap2D : Bitmap
		{
			uint32_t m_width;
			uint32_t m_height;
		public:
			Bitmap2D() = default;
			/** @see alloc. */
			Bitmap2D(
				Channel channel,
				Component component,
				uint32_t width,
				uint32_t height);

			/** Returns the pixel of the Bitmap at the given indices.
			@assert The Bitmap must exist.
			@assert The Bitmap must have the identical Channel and Component.
			@assert The indices must be within the Bitmap's bounds.
			@see Bitmap::pixel. */
			template<Channel c, Component co>
			RECXDA14 pixel_t<c,co> & pixel(uint32_t x, uint32_t y);
			/** Returns the pixel of the Bitmap at the given indices.
			@assert The Bitmap must exist.
			@assert The Bitmap must have the identical Channel and Component.
			@assert The indices must be within the Bitmap's bounds.
			@see Bitmap::pixel. */
			template<Channel c, Component co>
			RECXDA pixel_t<c,co> const& pixel(uint32_t x, uint32_t y) const;


			using Bitmap::exists;
			using Bitmap::size;
			using Bitmap::channel;

			/** Allocates the image data.
			@see Bitmap::alloc. */
			REINL void alloc(
				Channel channel,
				Component component,
				uint32_t width,
				uint32_t height);

			using Bitmap::free;

			/** Returns the width of the Bitmap.
			@assert The Bitmap must exist. */
			RECXDA uint32_t width() const;
			/** Returns the height of the Bitmap.
			@assert The Bitmap must exist. */
			RECXDA uint32_t height() const;

			/** Creates a mipmap using nearest filtering.
			@assert The Bitmap must exist.
			@assert The Bitmap must be larger than one pixel. */
			Bitmap2D create_mipmap_near() const;
			/** Creates a mipmap using linear filtering.
			@assert The Bitmap must exist.
			@assert The Bitmap must be larger than one pixel. */
			Bitmap2D create_mipmap_lin() const;

			/** Returns the mipmap's pixel at the given index using nearest filtering.
			@assert The index must be less than half the size of the Bitmap. */
			template<Channel ch, Component co>
			RECXDA pixel_t<ch,co> const& mip_near(uint32_t x, uint32_t y) const;
			/** Returns the mipmap's pixel at the given index using linear filtering.
			@assert The index must be less than half the size of the Bitmap. */
			template<Channel ch, Component co>
			RECXDA pixel_t<ch,co> mip_lin(uint32_t x, uint32_t y) const;

		};

		/** Represents a three dimensional image. */
		class Bitmap3D : Bitmap
		{
			uint32_t m_width;
			uint32_t m_height;
			uint32_t m_depth;

		public:
			Bitmap3D() = default;
			/** @see alloc. */
			Bitmap3D(
				Channel channel,
				Component component,
				uint32_t width,
				uint32_t height,
				uint32_t depth);

			/** Returns the pixel of the Bitmap at the given indices.
			@assert The Bitmap must exist.
			@assert The Bitmap must have the identical Channel and Component.
			@assert The indices must be within the Bitmap's bounds.
			@see Bitmap::pixel. */
			template<Channel c, Component co>
			RECXDA14 pixel_t<c,co> & pixel(uint32_t x, uint32_t y, uint32_t z);
			/** Returns the pixel of the Bitmap at the given indices.
			@assert The Bitmap must exist.
			@assert The Bitmap must have the identical Channel and Component.
			@assert The indices must be within the Bitmap's bounds.
			@see Bitmap::pixel. */
			template<Channel c, Component co>
			RECXDA pixel_t<c,co> const& pixel(uint32_t x, uint32_t y, uint32_t z) const;

			using Bitmap::exists;
			using Bitmap::size;
			using Bitmap::channel;

			/** Allocates the image data.
			@see Bitmap::alloc. */
			REINL void alloc(
				Channel channel,
				Component component,
				uint32_t width,
				uint32_t height,
				uint32_t depth);

			using Bitmap::free;

			/** Returns the width of the Bitmap.
			@assert The Bitmap must exist. */
			RECXDA uint32_t width() const;
			/** Returns the height of the Bitmap.
			@assert The Bitmap must exist. */
			RECXDA uint32_t height() const;
			/** Returns the depth of the Bitmap.
			@assert The Bitmap must exist. */
			RECXDA uint32_t depth() const;

			/** Creates a mipmap using nearest filtering.
			@assert The Bitmap must exist.
			@assert The Bitmap must be larger than one pixel. */
			Bitmap3D create_mipmap_near() const;
			/** Creates a mipmap using linear filtering.
			@assert The Bitmap must exist.
			@assert The Bitmap must be larger than one pixel. */
			Bitmap3D create_mipmap_lin() const;

			/** Returns the mipmap's pixel at the given index using nearest filtering.
			@assert The index must be less than half the size of the Bitmap. */
			template<Channel ch, Component co>
			RECXDA pixel_t<ch,co> const& mip_near(uint32_t x, uint32_t y, uint32_t z) const;
			/** Returns the mipmap's pixel at the given index using linear filtering.
			@assert The index must be less than half the size of the Bitmap. */
			template<Channel ch, Component co>
			RECXDA pixel_t<ch,co> mip_lin(uint32_t x, uint32_t y, uint32_t z) const;
		};
	}
}


#endif