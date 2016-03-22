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
			enum class TextureType
			{
				Texture1D,
				Texture1DArray,
				Texture2D,
				Texture2DArray,
				Texture2DMultisample,
				Texture2DMultisampleArray,
				Texture3D
			};

			class Texture : Handle
			{
				static void alloc_handles(handle_t * handles, size_t count);
				static void destroy_handles(handle_t * handles, size_t count);

			public:
				Texture();
				Texture(Texture &&) = default;
				Texture &operator=(Texture &&) = default;
				REINL ~Texture();

				using Handle::handle;
				using Handle::exists;

				virtual TextureType type() const = 0;
			};


			class Texture2D : public Texture
			{
				static handle_t bound;

				uint32
					m_width,
					m_height;
			public:
				Texture2D();
				Texture2D(Texture2D &&) = default;
				Texture2D &operator=(Texture2D &&) = default;
				REINL ~Texture2D();
				
				using Texture::handle;
				using Texture::exists;

				void bind();

				REINL TextureType type() const override;
			};

			class Texture2DArray : public Texture
			{
			public:
				Texture2DArray();
				Texture2DArray(Texture2DArray &&);
				Texture2DArray &operator=(Texture2DArray &&);
				REINL ~Texture2DArray();

				Texture2DArray(Texture2DArray const&) = default;
				Texture2DArray &operator=(Texture2DArray const&) = delete;


			};
		}
	}
}

#include "Texture.inl"

#endif