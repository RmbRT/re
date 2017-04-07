#ifndef __re_graphics_gl_texture_hpp_defined
#define __re_graphics_gl_texture_hpp_defined

#include "../../defines.hpp"
#include "../../types.hpp"

#include "Handle.hpp"
#include "Binding.hpp"
#include "Context.hpp"
#include "Version.hpp"
#include "../Bitmap.hpp"
#include "../../util/Lookup.hpp"

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			/** Represents a deriving class of Texture. */
			enum class TextureType
			{
				k1D,
				k2D,
				k3D,
				k2DMultisample,
				k1DArray,
				k2DArray,
				k2DMultisampleArray,
				kRectangle,
				kCubeMap,
				kCubeMapArray,
				RE_LAST(kBuffer)
			};

			enum class MipmapFilter
			{
				kNearest,
				RE_LAST(kLinear)
			};


			/** Used for `Texture::set_min_filter()`.
				Each field represents a method for choosing the pixel color when rendering staunched textures. */
			enum class TextureMinFilter
			{
				/** Uses the nearest texel of the base texture image. */
				kNearest,
				/** Interpolates between surrounding texels of the base texture image. */
				kLinear,
				/** Uses the nearset texel of the nearest mip map. */
				kNearestMipmapNearest,
				/** Interpolates between surrounding texels of the nearest mip map. */
				kNearestMipmapLinear,
				/** Interpolates between the nearest texels of the surrounding mip maps. */
				kLinearMipmapNearest,
				/** Interpolates between the surrounding texels of the surrounding mip maps. */
				RE_LAST(kLinearMipmapLinear)
			};

			enum class TextureMagFilter
			{
				kNearest,
				RE_LAST(kLinear)
			};
			/** Used for coniguring the parameters of a Texture. */
			enum class TextureWrap
			{
				kClamp,
				kRepeat,
				kClampToBorder,
				kClampToEdge,
				RE_LAST(kMirroredRepeat)
			};
			/** Used for coniguring the parameters of a Texture. */
			enum class TextureCompareMode
			{
				kCompareRToTexture,
				RE_LAST(kNone)
			};
			/** Used for coniguring the parameters of a Texture. */
			enum class TextureCompareFunc
			{
				kLessEqual,
				kGreaterEqual,
				kLess,
				kGreater,
				kEqual,
				kNotEqual,
				kAlways,
				RE_LAST(kNever)
			};
			/** Used for coniguring the parameters of a Texture. */
			enum class DepthTextureMode
			{
				kLuminance,
				kIntensity,
				RE_LAST(kAlpha)
			};

			/** The Texture base class.
				Textures must be allocated and destroyed manually. This is done via calling `Texture::alloc()` and `Texture::destroy()`. */
			class Texture : protected Handle
			{
				/** The currently bound textures.
					This is used to reduce the overhead of the `bind()` and `unbind()` functions. */
				static util::Lookup<TextureType, Binding> s_binding;

				/** The type of the texture.
					This is already defined by the deriving type, but was chosen instead of a virtual getter function. */
				TextureType const m_type;

			protected:
				/** Creates an unallocated texture with of the given type.
				@param[in] type:
					The type of the texture. */
				RECX Texture(
					TextureType type);
			private:
				/** Whether the Texture is bound.
				@assert The Texture must exist. */
				REIL bool bound() const;

			public:
				Texture(Texture &&) = default;
				Texture &operator=(Texture &&) = default;

				using Handle::handle;
				using Handle::exists;

				/** Used to identify the deriving class of Texture. */
				REIL TextureType type() const;

				/** Allocates the given Textures.
				@assert
					None of the addresses may be null.
					None of the given Textures may exist yet.
				@param[in] textures:
					The addresses of the Textures to be allocated.
				@param[in] count:
					How many Textures to allocate.
				@sideeffect
					Allocates the Handle held by each passed Texture.
				@see `util::allocation_buffer()`. */
				static void alloc(
					Texture ** textures,
					size_t count);
				/** Destroys the given Textures.
				@param[in] textures:
					The addresses of the Textures to be destroyed.
				@param[in] count:
					How many Textures to destroy.
				@important
					None of the addresses may be null.
					All of the given Textures must exist.
				@sideeffect
					Destroys the Handle held by each passed Texture.
					Unbinds a bound Texture when it is destroyed.
				@see `util::allocation_buffer()`. */
				static void destroy(
					Texture ** textures,
					size_t count);

				void set_mag_filter(TextureMagFilter mag);
				void set_min_filter(TextureMinFilter min);
				void set_s_wrap(TextureWrap wrap);
			protected:
				void set_t_wrap(TextureWrap wrap);
				void set_r_wrap(TextureWrap wrap);
			public:
				/** Sets the border color for the texture.
					This only has an effect for textures that have `TextureWrap::kClampToBorder` as thier wrap options. */
				void set_border_color(
                    math::Vec4<float> const& color);

				/** Sets the priority with which the texture should be kept in memory.
				@assert
					The texture must exist.
				@param[in] priority:
					The priority value, in the range of `[0, 1]`, where 0 is the lowest priority, and 1 the highest. */
				void set_memory_priority(
					float priority);

				/** Lets OpenGL generate the mip maps of the texture's base image.
					Requires an OpenGL version 3.0+ context.
				@assert
					The texture must exist. */
				void generate_mipmaps();

				/** Binds the Texture to make it usable. */
				void bind();
			};

			/** 1-dimensional texture type. */
			class Texture1D : public Texture
			{
				/** The width of the texture, in texels. */
				uint_t m_size;
			public:
				/** Creates an unallocated texture. */
				RECX Texture1D();
				Texture1D(Texture1D &&) = default;
				Texture1D &operator=(Texture1D &&) = default;

				REIL static bool available();

				/** Returns the size of the Texture.
				@assert The Texture must exist. */
				REIL uint_t size() const;

				/** Resizes the Texture to match the size of the given Bitmap, and sets the given Bitmap as image of the requested mipmap level.
				@assert
					The texture must exist.
				@param[in] texels:
					The image data to set.
				@param[in] lod:
					The mipmap level to set. 0 for the base image. */
				void set_texels(
					Bitmap1D const& texels,
					uint_t lod);

				/** Sets the texel data of the texture to the given bitmap, and creates mip maps based on it.
					Mip maps will be generated using the requested filter method and the given base texel image bitmap. This does not update the texture properties, they have to be updated manually via `upload_params()`. The new mip map level gets set to the 
				@assert
					The texture must exist.
				@assert
					The given bitmap must exist.
				@param[in] base_texels:
					The base image data to set the texture to.
				@param[in] filter:
					The method used to calculate the mip maps.
				@return
					The amount of mip maps generated, with 0 being only the base image. */
				uint_t set_texels_mipmap(
					Bitmap1D const& base_texels,
					MipmapFilter filter);

				/** Resizes the Texture to the given size.
					Allocates an uninitialised texture of the requested size.
				@assert
					The texture must exist.
				@param[in] size:
					The new size of the texture.
				@param[in] component:
					The new color component of the texture.
				@param[in] channel:
					The new color channel of the texture. */
				void resize(
					uint_t size,
					Component component,
					Channel channel);

				/** Unbinds the currently bound Texture1D, if any. */
				static void unbind();
			};

			/** 2-dimensional texture type. */
			class Texture2D : public Texture
			{
				/** The texel width of the texture. */
				uint_t m_width;
				/** The texel height of the texture. */
				uint_t m_height;
			public:
				/** Constructs an unallocated 2-dimensional texture. */
				RECX Texture2D();
				Texture2D(Texture2D &&) = default;
				Texture2D &operator=(Texture2D &&) = default;

				REIL static bool available();

				/** Returns the width of the Texture.
				@assert The Texture must exist. */
				REIL uint_t width() const;
				/** Returns the height of the Texture.
				@assert The Texture must exist. */
				REIL uint_t height() const;

				/** Unbinds the currently bound Texture2D, if any. */
				static void unbind();

				/** Sets the image data of the texture.
				@assert
					The texture must exist.
				@param[in] texels:
					The image data.
				@param[in] lod:
					The mipmap level to set the data for. */
				void set_texels(
					Bitmap2D const& texels,
					uint_t lod);

				/** Sets the image data of the texture and generates mip maps.
				@assert
					The texture must exist.
				@assert
					The bitmap must exist.
				@param[in] base_texels:
					The base image of the texture.
				@param[in] filter:
					The filter method used to generate the mip maps.
				@return
					The number of mip maps generated, with 0 meaning only the base image was set, and no mip maps were generated. */
				uint_t set_texels_mipmap(
					Bitmap2D const& base_texels,
					MipmapFilter filter);

				/** Resizes the Texture to the given size.
					Allocates an uninitialised texture of the requested size.
				@assert
					The texture must exist.
				@param[in] width:
					The new width of the texture.
				@param[in] height:
					The new height of the texture.
				@param[in] component:
					The new color component of the texture.
				@param[in] channel:
					The new color channel of the texture. */
				void resize(
					uint_t width,
					uint_t height,
					Channel channel,
					Component component);
			};

			/** 3-dimensional texture type. */
			class Texture3D : public Texture
			{
				/** The texel width of the texture. */
				uint_t m_width;
				/** The texel height of the texture. */
				uint_t m_height;
				/** The texel depth of the texture. */
				uint_t m_depth;
			public:
				/** Constructs an unallocated 3-dimensional texture. */
				RECX Texture3D();
				Texture3D(Texture3D &&) = default;
				Texture3D &operator=(Texture3D &&) = default;

				REIL static bool available();

				/** Returns the width of the texture.
				@assert The Texture must exist. */
				REIL uint_t width() const;
				/** Returns the height of the texture.
				@assert The Texture must exist. */
				REIL uint_t height() const;
				/** Returns the depth of the texture.
				@assert The Texture must exist. */
				REIL uint_t depth() const;

				/** Unbinds the currently bound Texture3D, if any. */
				static void unbind();

				/** Sets the image data of the texture.
				@assert
					The texture must exist.
				@param[in] texels:
					The image data.
				@param[in] lod:
					The mipmap level to set the data for. */
				void set_texels(
					Bitmap3D const& texels,
					uint_t lod);
			};

			/** GL_TEXTURE_2D_MULTISAMPLE texture class. */
			class Texture2DMultisample : public Texture
			{
				/** The texture's texel width. */
				uint_t m_width;
				/** The texture's texel height. */
				uint_t m_height;
				/** The texture's sample count.*/
				uint_t m_samples;
			public:
				/** Constructs an unallocated 2-dimensional multisampled texture. */
				RECX Texture2DMultisample();
				Texture2DMultisample(Texture2DMultisample &&) = default;
				Texture2DMultisample &operator=(Texture2DMultisample &&) = default;

				REIL static bool available();

				/** Returns the width of the Texture.
				@assert The Texture must exist. */
				REIL uint_t width() const;
				/** Returns the height of the Texture.
				@assert The Texture must exist. */
				REIL uint_t height() const;
				/** Returns the samples of the Texture.
				@assert The Texture must exist. */
				REIL uint_t samples() const;

				/** unbinds the currently bound Texture2DMultisample, if any. */
				static void unbind();
			};

			/** GL_TEXTURE_1D_ARRAY texture class. */
			class Texture1DArray : public Texture
			{
				/** The texture's texel size. */
				uint_t m_size;
				/** The texture's layers. */
				uint_t m_layers;
			public:
				/** Constructs an unallocated 1-dimensional array texture. */
				RECX Texture1DArray();
				Texture1DArray(Texture1DArray &&) = default;
				Texture1DArray &operator=(Texture1DArray &&) = default;

				/** @return The size of the texture.
				@assert The Texture must exist. */
				REIL uint_t size() const;
				/** @return The layers of the texture.
				@assert The Texture must exist. */
				REIL uint_t layers() const;

				static void unbind();
			};

			/** GL_TEXTURE_2D_ARRAY texture class. */
			class Texture2DArray : public Texture
			{
				uint_t
					m_width,
					m_height,
					m_layers;
			public:
				RECX Texture2DArray();
				Texture2DArray(Texture2DArray &&) = default;
				Texture2DArray &operator=(Texture2DArray &&) = default;

				REIL static bool available();

				REIL uint_t width() const;
				REIL uint_t height() const;
				REIL uint_t layers() const;

				static void unbind();
			};

			/** GL_TEXTURE_2D_MULTISAMPLE_ARRAY texture class. */
			class Texture2DMultisampleArray : public Texture
			{
				uint_t
					m_width,
					m_height,
					m_samples,
					m_layers;
			public:
				RECX Texture2DMultisampleArray();
				Texture2DMultisampleArray(Texture2DMultisampleArray &&) = default;
				Texture2DMultisampleArray &operator=(Texture2DMultisampleArray &&) = default;

				REIL static bool available();

				REIL uint_t width() const;
				REIL uint_t height() const;
				REIL uint_t samples() const;
				REIL uint_t layers() const;

				static void unbind();
			};
			/** GL_TEXTURE_RECTANGLE texture class. */
			class TextureRectangle : public Texture
			{
				uint_t
					m_width,
					m_height;
			public:
				RECX TextureRectangle();
				TextureRectangle(TextureRectangle &&) = default;
				TextureRectangle &operator=(TextureRectangle &&) = default;

				REIL static bool available();

				REIL uint_t width() const;
				REIL uint_t height() const;

				static void unbind();
			};

			class TextureCubemap : public Texture
			{
			public:
				RECX TextureCubemap();

				TextureCubemap(TextureCubemap &&) = default;
				TextureCubemap &operator=(TextureCubemap &&) = default;

				REIL static bool available();

				REIL uint_t size() const;
			};

			class TextureCubemapArray : public Texture
			{
				uint_t m_width;
				uint_t m_height;
			public:
				RECX TextureCubemapArray();

				TextureCubemapArray(TextureCubemapArray &&) = default;
				TextureCubemapArray &operator=(TextureCubemapArray &&) = default;

				REIL static bool available();

				REIL uint_t size() const;
				REIL uint_t layers() const;
			};
		}
	}
}

#include "Texture.inl"

#endif
