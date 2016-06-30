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
		enum class Channel : ubyte_t
		{
			kR,
			kRg,
			kRgb,
			RE_LAST(kRgba)
		};

		/** Describes the type of the color component a Bitmap has. */
		enum class Component : ubyte_t
		{
			kFloat,
			RE_LAST(kUbyte)
		};

		namespace detail
		{
			template<Component kComponent>
			struct ComponentType;

			template<>
			struct ComponentType<Component::kFloat> { typedef float type_t; };
			template<>
			struct ComponentType<Component::kUbyte> { typedef ubyte_t type_t; };

			template<Component kComponent>
			using component_t = typename ComponentType<kComponent>::type_t;

			template<Channel kChannel, Component kComponent>
			struct Pixel;

			template<Component kComponent>
			struct Pixel<Channel::kR, kComponent> { typedef component_t<kComponent> type; };
			template<Component kComponent>
			struct Pixel<Channel::kRg, kComponent> { typedef math::vec2<component_t<kComponent>> type; };
			template<Component kComponent>
			struct Pixel<Channel::kRgb, kComponent> { typedef math::vec3<component_t<kComponent>> type; };
			template<Component kComponent>
			struct Pixel<Channel::kRgba, kComponent> { typedef math::vec4<component_t<kComponent>> type; };

		}

		template<Channel kChannel, Component kComponent>
		using pixel_t = typename detail::Pixel<kChannel, kComponent>::type;

		/** Represents an Image. */
		class Bitmap
		{
			/** The channel of the bitmap. */
			Channel m_channel;
			/** The component of the bitmap. */
			Component m_component;
			/** The count of elements, not bytes. */
			uint32_t m_size;
			/** The data buffer. */
			void* m_data;
		public:
			/** Constructs a non-allocated Bitmap. */
			RECX Bitmap();
			/** Constructs an allocated Bitmap with the given Channel and Component and size.
			@param[in] channel:
				The number of channels the Bitmap should have.
			@param[in] component:
				The component type the Bitmap should have.
			@param[in] size:
				The pixel count the Bitmap should have. */
			Bitmap(
				Channel channel,
				Component component,
				uint32_t size);
			/** Copies a bitmap.
			@param[in] rhs:
				The bitmap to copy from. */
			Bitmap(
				Bitmap const& rhs);
			/** Moves a bitmap.
			@param[in] rhs:
				The bitmap to move from.
				Will be invalidated after the call. */
			Bitmap(
				Bitmap && rhs);
			/** Copies a bitmap, freeing the old bitmap, if exists.
			@param[in] rhs:
				The bitmap to copy from.
			@return
				The bitmap that was copied to. */
			Bitmap &operator=(
				Bitmap const& rhs);
			/** Moves a bitmap freeing the old bitmap, if exists.
			@param[in] rhs:
				The bitmap to move from.
				Will be invalidated after the call.
			@return
				The bitmap that was copied to. */
			Bitmap &operator=(Bitmap && rhs);
			/** Frees the Bitmap if it was still allocated. */
			~Bitmap();

			/** Allocates the image data with the given channels and bounds. */
			void alloc(Channel channel, Component component, uint32_t size);
			/** Frees the image data. */
			void free();

			/** Returns whether the Bitmap contains image data. */
			REIL bool exists() const;
			/** Returns the pixel count of the Bitmap's image data, not the byte count.
			@assert The Bitmap must exist. */
			REIL uint32_t size() const;
			/** Returns the Channel of this Bitmap.
			@assert The Bitmap must exist. */
			REIL Channel channel() const;
			/** Returns the Component of this Bitmap.
			@assert The Bitmap must exist. */
			REIL Component component() const;

			/** Returns the pixel of the Bitmap at the given index.
			@assert The Bitmap must exist.
			@assert The Bitmap must have the identical Channel and Component.
			@assert index must be within the Bitmap's bounds. */
			template<Channel kChannel, Component kComponent>
			REIL pixel_t<kChannel,kComponent> & pixel(uint32_t index);
			/** Returns the pixel of the Bitmap at the given index.
			@assert The Bitmap must exist.
			@assert The Bitmap must have the identical Channel and Component.
			@assert index must be within the Bitmap's bounds. */
			template<Channel kChannel, Component kComponent>
			REIL pixel_t<kChannel,kComponent> const& pixel(uint32_t index) const;

			REIL void * data();
			REIL void const * data() const;
			size_t byte_size() const;
		};

		/** Represents a one dimensional image. */
		class Bitmap1D : Bitmap
		{
		public:
			RECX Bitmap1D();
			/** @see Bitmap::Bitmap. */
			Bitmap1D(
				Channel channel,
				Component component,
				uint32_t size);

			using Bitmap::pixel;

			using Bitmap::exists;
			using Bitmap::size;
			using Bitmap::channel;
			using Bitmap::alloc;
			using Bitmap::free;
			using Bitmap::data;
			using Bitmap::byte_size;
			using Bitmap::component;

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
			REIL pixel_t<ch,co> const& mip_near(
				uint32_t index) const;
			/** Returns the mipmap's pixel at the given index using linear filtering.
			@assert The index must be less than half the size of the Bitmap. */
			template<Channel ch, Component co>
			REIL pixel_t<ch,co> mip_lin(
				uint32_t index) const;
		};

		/** Represents a two dimensional image. */
		class Bitmap2D : Bitmap
		{
			uint32_t m_width;
			uint32_t m_height;
		public:
			RECX Bitmap2D();
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
			REIL pixel_t<c,co> & pixel(uint32_t x, uint32_t y);
			/** Returns the pixel of the Bitmap at the given indices.
			@assert The Bitmap must exist.
			@assert The Bitmap must have the identical Channel and Component.
			@assert The indices must be within the Bitmap's bounds.
			@see Bitmap::pixel. */
			template<Channel c, Component co>
			REIL pixel_t<c,co> const& pixel(uint32_t x, uint32_t y) const;


			using Bitmap::exists;
			using Bitmap::size;
			using Bitmap::channel;
			using Bitmap::data;
			using Bitmap::byte_size;
			using Bitmap::component;

			/** Allocates the image data.
			@see Bitmap::alloc. */
			REIL void alloc(
				Channel channel,
				Component component,
				uint32_t width,
				uint32_t height);

			using Bitmap::free;

			/** Returns the width of the Bitmap.
			@assert The Bitmap must exist. */
			REIL uint32_t width() const;
			/** Returns the height of the Bitmap.
			@assert The Bitmap must exist. */
			REIL uint32_t height() const;

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
			REIL pixel_t<ch,co> const& mip_near(uint32_t x, uint32_t y) const;
			/** Returns the mipmap's pixel at the given index using linear filtering.
			@assert The index must be less than half the size of the Bitmap. */
			template<Channel ch, Component co>
			REIL pixel_t<ch,co> mip_lin(uint32_t x, uint32_t y) const;

		};

		/** Represents a three dimensional image. */
		class Bitmap3D : Bitmap
		{
			uint32_t m_width;
			uint32_t m_height;
			uint32_t m_depth;

		public:
			RECX Bitmap3D();
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
			REIL pixel_t<c,co> & pixel(uint32_t x, uint32_t y, uint32_t z);
			/** Returns the pixel of the Bitmap at the given indices.
			@assert The Bitmap must exist.
			@assert The Bitmap must have the identical Channel and Component.
			@assert The indices must be within the Bitmap's bounds.
			@see Bitmap::pixel. */
			template<Channel c, Component co>
			REIL pixel_t<c,co> const& pixel(uint32_t x, uint32_t y, uint32_t z) const;

			using Bitmap::exists;
			using Bitmap::size;
			using Bitmap::channel;
			using Bitmap::data;
			using Bitmap::byte_size;
			using Bitmap::component;

			/** Allocates the image data.
			@see Bitmap::alloc. */
			REIL void alloc(
				Channel channel,
				Component component,
				uint32_t width,
				uint32_t height,
				uint32_t depth);

			using Bitmap::free;

			/** Returns the width of the Bitmap.
			@assert The Bitmap must exist. */
			REIL uint32_t width() const;
			/** Returns the height of the Bitmap.
			@assert The Bitmap must exist. */
			REIL uint32_t height() const;
			/** Returns the depth of the Bitmap.
			@assert The Bitmap must exist. */
			REIL uint32_t depth() const;

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
			REIL pixel_t<ch,co> const& mip_near(uint32_t x, uint32_t y, uint32_t z) const;
			/** Returns the mipmap's pixel at the given index using linear filtering.
			@assert The index must be less than half the size of the Bitmap. */
			template<Channel ch, Component co>
			REIL pixel_t<ch,co> mip_lin(uint32_t x, uint32_t y, uint32_t z) const;
		};
	}
}

#include "Bitmap.inl"

#endif