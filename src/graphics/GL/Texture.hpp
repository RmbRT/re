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
			class Texture : Handle
			{
				static void alloc_handles(handle_t * handles, size_t count);
				static void destroy_handles(handle_t * handles, size_t count);

			public:
				Texture();
				Texture(Texture &&);
				Texture &operator=(Texture &&);
				REINL ~Texture();

				using Handle::handle;
				using Handle::exists;

				Texture(Texture const&) = delete;
				Texture &operator=(Texture const&) = delete;
			};


			class Texture2D : Texture
			{
				static handle_t bound;

				uint32
					m_width,
					m_height;
			public:
				Texture2D();
				Texture2D(Texture2D &&);
				Texture2D &operator=(Texture2D &&);
				REINL ~Texture2D();
				
				Texture2D(Texture2D const&) = delete;
				Texture2D &operator=(Texture2D const&) = delete;

				using Texture::handle;
				using Texture::exists;

				void bind();
			};

			class Texture2DArray : Texture
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

#endif