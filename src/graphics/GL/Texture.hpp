//#ifndef __re_graphics_gl_texture_hpp_defined
#define __re_graphics_gl_texture_hpp_defined

#include "../../defines.hpp"
#include "../../types.hpp"

#include "Handle.hpp"
#include "../Bitmap.hpp"

namespace re
{
	namespace graphics
	{
		namespace GL
		{
			/** Represents a deriving class of Texture. */
			enum class TextureType
			{
				Texture1D,
				Texture2D,
				Texture3D,
				Texture2DMultisample,
				Texture1DArray,
				Texture2DArray,
				Texture2DMultisampleArray,
				TextureRectangle,
				TextureCubeMap,
				TextureCubeMapArray,
				TextureBuffer
			};

			/** The Texture base class. */
			class Texture : protected Handle
			{
				/** The deriving type of Texture. */
				TextureType m_type;
			protected:
				/** Creates an empty Texture Handle, and does not allocate the Texture on the GPU.
				@param[in] type: The TextureType constant used to represent the deriving class of the Texture. */
				Texture(TextureType type);
			public:
				Texture(Texture &&) = default;
				Texture &operator=(Texture &&) = default;

				using Handle::handle;
				using Handle::exists;

				/** Used to identify the deriving class of Texture. */
				REINL TextureType type() const;

				/** Allocates the given Textures.
				@param[in] textures:
					The addresses of the Textures to be allocated.
				@param[in] count:
					How many Textures to allocate.
				@important
					None of the addresses must be null.
					None of the given Textures must exist yet.
				@sideeffect
					Allocates the Handle held by each passed Texture.
				@see util::allocation_buffer. */
				static void alloc(Texture ** textures, size_t count);
				/** Destroys the given Textures.
				@param[in] textures:
					The addresses of the Textures to be destroyed.
				@param[in] count:
					How many Textures to destroy.
				@important
					None of the addresses must be null.
					All of the given Textures must exist.
				@sideeffect
					Destroys the Handle held by each passed Texture.
					Unbinds a bound Texture when it is destroyed.
				@see util::allocation_buffer. */
				static void destroy(Texture ** textures, size_t count);
			};

			class Texture1D : public Texture
			{
				static handle_t bound;

				uint m_size;
			public:
				Texture1D();
				Texture1D(Texture1D &&) = default;
				Texture1D &operator=(Texture1D &&) = default;

				REINL uint size() const;

				/** Resizes the Texture to match the size of the given Bitmap, and sets the given Bitmap as image. */
				void set_texels(Bitmap const& texels);
				/** Resizes the Texture to the given size. */
				void resize(uint size);
			};

			class Texture2D : public Texture
			{
				static handle_t bound;

				uint
					m_width,
					m_height;
			public:
				Texture2D();
				Texture2D(Texture2D &&) = default;
				Texture2D &operator=(Texture2D &&) = default;

				static void unbind();

				void bind();

				REINL TextureType type() const override;
			};

			class Texture3D : public Texture
			{
				static handle_t bound;

				uint
					m_width,
					m_height,
					m_depth;
			public:
				Texture3D();
				Texture3D(Texture3D &&) = default;
				Texture3D &operator=(Texture3D &&) = default;

				static void unbind();

				void bind();

				REINL uint width() const;
				REINL uint height() const;
				REINL uint depth() const;
			};

			class Texture2DMultisample : public Texture
			{
				static handle_t bound;

				uint
					m_width,
					m_height,
					m_samples;
			public:
				Texture2DMultisample();
				Texture2DMultisample(Texture2DMultisample &&) = default;
				Texture2DMultisample &operator=(Texture2DMultisample &&) = default;

				static void unbind();

				void bind();

				REINL uint width() const;
				REINL uint height() const;
				REINL uint samples() const;
			};

			class Texture1DArray : public Texture
			{
				static handle_t bound;

				uint
					m_size,
					m_layers;
			public:
				Texture1DArray();
				Texture1DArray(Texture1DArray &&) = default;
				Texture1DArray &operator=(Texture1DArray &&) = default;

				static void unbind();

				void bind();

				REINL uint size() const;
				REINL uint layers() const;
			};

			class Texture2DArray : public Texture
			{
				static handle_t bound;

				uint
					m_width,
					m_height,
					m_layers;
			public:
				Texture2DArray();
				Texture2DArray(Texture2DArray &&) = default;
				Texture2DArray &operator=(Texture2DArray &&) = default;

				static void unbind();

				void bind();
				
				REINL uint width() const;
				REINL uint height() const;
				REINL uint layers() const;
			};

			class Texture2DMultisampleArray : public Texture
			{
				static handle_t bound;

				uint
					m_width,
					m_height,
					m_samples,
					m_layers;
			public:
				Texture2DMultisampleArray();
				Texture2DMultisampleArray(Texture2DMultisampleArray &&) = default;
				Texture2DMultisampleArray &operator=(Texture2DMultisampleArray &&) = default;

				static void unbind();

				void bind();

				REINL uint width() const;
				REINL uint height() const;
				REINL uint samples() const;
				REINL uint layers() const;
			};

			class TextureRectangle : public Texture
			{
				static handle_t bound;

				uint
					m_width,
					m_height;
			};
		}
	}
}

#include "Texture.inl"

#endif