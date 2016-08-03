#ifndef __re_graphics_gl_texture_hpp_defined
#define __re_graphics_gl_texture_hpp_defined

#include "../../defines.hpp"
#include "../../types.hpp"

#include "Handle.hpp"
#include "Binding.hpp"
#include "../Bitmap.hpp"

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

			/** The Texture base class.
				Textures must be allocated and destroyed manually. This is done via calling `Texture::alloc()` and `Texture::destroy()`. */
			class Texture : protected Handle
			{
				/** The currently bound textures.
					This is used to reduce the overhead of the `bind()` and `unbind()` functions. */
				static Binding s_binding[RE_COUNT(TextureType)];

				/** The type of the texture.
					This is already defined by the deriving type, but was chosen instead of a virtual getter function. */
				TextureType m_type;
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

				/** Binds the Texture to make it usable. */
				void bind();
			};

			class Texture1D : public Texture
			{
				uint_t m_size;
			public:
				RECX Texture1D();
				Texture1D(Texture1D &&) = default;
				Texture1D &operator=(Texture1D &&) = default;

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
				void set_texels(Bitmap const& texels, uint_t lod);
				/** Resizes the Texture to the given size.
				@assert
					The texture must exist. */
				void resize(uint_t size);

				/** Unbinds the currently bound Texture1D, if any. */
				static void unbind();
			};

			class Texture2D : public Texture
			{
				uint_t
					m_width,
					m_height;
			public:
				RECX Texture2D();
				Texture2D(Texture2D &&) = default;
				Texture2D &operator=(Texture2D &&) = default;

				/** Returns the width of the Texture.
				@assert The Texture must exist. */
				REIL uint_t width() const;
				/** Returns the height of the Texture.
				@assert The Texture must exist. */
				REIL uint_t height() const;

				/** Unbinds the currently bound Texture2D, if any. */
				static void unbind();
			};

			class Texture3D : public Texture
			{
				uint_t
					m_width,
					m_height,
					m_depth;
			public:
				RECX Texture3D();
				Texture3D(Texture3D &&) = default;
				Texture3D &operator=(Texture3D &&) = default;

				/** Returns the width of the Texture.
				@assert The Texture must exist. */
				REIL uint_t width() const;
				/** Returns the height of the Texture.
				@assert The Texture must exist. */
				REIL uint_t height() const;
				/** Returns the depth of the Texture.
				@assert The Texture must exist. */
				REIL uint_t depth() const;

				/** Unbinds the currently bound Texture3D, if any. */
				static void unbind();
			};

			class Texture2DMultisample : public Texture
			{
				uint_t
					m_width,
					m_height,
					m_samples;
			public:
				RECX Texture2DMultisample();
				Texture2DMultisample(Texture2DMultisample &&) = default;
				Texture2DMultisample &operator=(Texture2DMultisample &&) = default;

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

			class Texture1DArray : public Texture
			{
				uint_t
					m_size,
					m_layers;
			public:
				RECX Texture1DArray();
				Texture1DArray(Texture1DArray &&) = default;
				Texture1DArray &operator=(Texture1DArray &&) = default;

				REIL uint_t size() const;
				REIL uint_t layers() const;

				static void unbind();
			};

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

				REIL uint_t width() const;
				REIL uint_t height() const;

				static void unbind();
			};
		}
	}
}

#include "Texture.inl"

#endif