#include "Texture.hpp"
#include "OpenGL.hpp"

namespace re
{
	namespace graphics
	{
		namespace gl
		{

			GLenum gl_internalformat(ColorChannel channel)
			{
				static GLenum const k_lookup[] = {
					GL_RED,
					GL_RG,
					GL_RGB,
					GL_RGBA,
					GL_RED,
					GL_RG,
					GL_RGB,
					GL_RGBA
				};

				RE_DBG_ASSERT(size_t(channel) < _countof(k_lookup));

				return k_lookup[channel];
			}

			GLenum gl_format(ColorChannel channel)
			{
				return gl_internalformat(channel);
			}

			GLenum gl_type(ColorChannel channel)
			{
				static GLenum const lookup[] = {
					GL_FLOAT,
					GL_FLOAT,
					GL_FLOAT,
					GL_FLOAT,
					GL_UNSIGNED BYTE,
					GL_UNSIGNED BYTE,
					GL_UNSIGNED BYTE,
					GL_UNSIGNED BYTE
				};

				RE_DBG_ASSERT(size_t(channel) < _countof(lookup));

				return lookup[channel];
			}

			void Texture::alloc(Texture ** textures, size_t count)
			{
				RE_DBG_ASSERT(textures);

				Handle * const handles = util::allocation_buffer<Handle>(count);

				RE_OGL(glGenTextures(count, handles));

				for(size_t i = count; i--;)
				{
					RE_DBG_ASSERT(textures[i]);
					RE_DBG_ASSERT(!textures[i]->exists());
					textures[i]->set_handle(handles[i]);
				}
			}

			void Texture::destroy(Texture ** textures, size_t count)
			{
				RE_DBG_ASSERT(textures);

				Handle * const handles = util::allocation_buffer<Handle>(count);

				for(size_t i = count; i--;)
				{
					RE_DBG_ASSERT(textures[i]);
					RE_DBG_ASSERT(textures[i]->exists());
					handles[i] = textures[i]->handle();

					s_binding[size_t(textures[i]->type())].on_invalidate(texures[i]->handle());
				}

				RE_OGL(glDeleteTextures(count, handles));
			}

			void Texture::bind()
			{
				RE_DBG_ASSERT(exists());

				if(!bound())
				{
					binding[size_t(type())].bind(handle());

					static GLenum const targets = {
						GL_TEXTURE_1D,
						GL_TEXTURE_2D,
						GL_TEXTURE_3D,
						GL_TEXTURE_2D_MULTISAMPLE,
						GL_TEXTURE_1D_ARRAY,
						GL_TEXTURE_2D_ARRAY,
						GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
						GL_TEXTURE_RECTANGLE,
						GL_TEXTURE_CUBE_MAP,
						GL_TEXTURE_CUBE_MAP_ARRAY,
						GL_TEXTURE_BUFFER
					};

					RE_DBG_ASSERT(size_t(type()) < _countof(targets));

					RE_OGL(glBindTexture(targets[size_t(type)], handle()));
				}
			}

			Texture1D::Texture1D():
				Texture(TextureType::Texture1D)
			{
			}

			void Texture1D::set_texels(Bitmap const& texels, uitn lod)
			{
				RE_DBG_ASSERT(exists());

				bind();

				RE_OGL(glTexImage1d(
					GL_TEXTURE_1D,
					lod,
					gl_internalformat(texels.channel()),
					texels.width(),
					0,
					gl_format(texels.channel()),
					gl_type(texels.channel()),
					texels.data()));
			}
		}
	}
}