#include "Texture.hpp"
#include "OpenGL.hpp"
#include "../../util/Lookup.hpp"
#include "../../util/AllocationBuffer.hpp"

namespace re
{
	namespace graphics
	{
		namespace gl
		{
			static REIL GLenum get_internalformat(
				graphics::Channel channel)
			{
				static util::Lookup<Channel, GLenum> const k_lookup = {
					{Channel::kR, (GLenum) GL_RED},
					{Channel::kRg, (GLenum) GL_RG},
					{Channel::kRgb, (GLenum) GL_RGB},
					{Channel::kRgba, (GLenum) GL_RGBA}
				};

				return k_lookup[channel];
			}

			static REIL GLenum get_format(
				Channel channel)
			{
				return get_internalformat(channel);
			}

			static GLenum get_type(
				Component component)
			{
				static util::Lookup<Component, GLenum> const k_lookup = {
					{Component::kFloat, GL_FLOAT},
					{Component::kUbyte, GL_UNSIGNED_BYTE}
				};

				return k_lookup[component];
			}

			static REIL GLenum get_target(
				TextureType type)
			{
				static util::Lookup<TextureType, GLenum> const k_targets = {
					{ TextureType::k1D, GL_TEXTURE_1D },
					{ TextureType::k2D, GL_TEXTURE_2D },
					{ TextureType::k3D, GL_TEXTURE_3D },
					{ TextureType::k2DMultisample, GL_TEXTURE_2D_MULTISAMPLE },
					{ TextureType::k1DArray, GL_TEXTURE_1D_ARRAY },
					{ TextureType::k2DArray, GL_TEXTURE_2D_ARRAY },
					{ TextureType::k2DMultisampleArray, GL_TEXTURE_2D_MULTISAMPLE_ARRAY },
					{ TextureType::kRectangle, GL_TEXTURE_RECTANGLE },
					{ TextureType::kCubeMap, GL_TEXTURE_CUBE_MAP },
					{ TextureType::kCubeMapArray, GL_TEXTURE_CUBE_MAP_ARRAY },
					{ TextureType::kBuffer, GL_TEXTURE_BUFFER }
				};

				return k_targets[type];
			}

			static REIL GLenum get_wrap(
				TextureWrap wrap)
			{
				static util::Lookup<TextureWrap, GLenum> const k_lookup = {
					{TextureWrap::kClamp, GL_CLAMP},
					{TextureWrap::kRepeat, GL_REPEAT},
					{TextureWrap::kClampToBorder, GL_CLAMP_TO_BORDER},
					{TextureWrap::kClampToEdge, GL_CLAMP_TO_EDGE},
					{TextureWrap::kMirroredRepeat, GL_MIRRORED_REPEAT}
				};

				return k_lookup[wrap];
			}

			void Texture::alloc(
				Texture ** textures,
				size_t count)
			{
				RE_DBG_ASSERT(textures);

				handle_t * const handles = util::allocation_buffer<handle_t>(count);

				RE_OGL(glGenTextures(count, handles));

				for(size_t i = count; i--;)
				{
					RE_DBG_ASSERT(textures[i]);
					RE_DBG_ASSERT(!textures[i]->exists());
					textures[i]->set_handle(handles[i]);
				}
			}

			void Texture::destroy(
				Texture ** textures,
				size_t count)
			{
				RE_DBG_ASSERT(textures);

				handle_t * const handles = util::allocation_buffer<handle_t>(count);

				for(size_t i = count; i--;)
				{
					RE_DBG_ASSERT(textures[i]);
					RE_DBG_ASSERT(textures[i]->exists());
					RE_DBG_ASSERT(RE_IN_ENUM(textures[i]->type(), TextureType));

					handles[i] = textures[i]->handle();

					s_binding[textures[i]->type()].on_invalidate(textures[i]->handle());
				}

				RE_OGL(glDeleteTextures(count, handles));
			}

			void Texture::set_mag_filter(
				TextureMagFilter filter)
			{
				RE_DBG_ASSERT(exists());

				static util::Lookup<TextureMagFilter, GLenum> const k_lookup = {
					{TextureMagFilter::kNearest, GL_NEAREST},
					{TextureMagFilter::kLinear, GL_LINEAR}
				};

				bind();

				RE_OGL(glTexParameteri(get_target(m_type), GL_TEXTURE_MAG_FILTER, k_lookup[filter]));
			}

			void Texture::set_min_filter(
				TextureMinFilter filter)
			{
				RE_DBG_ASSERT(exists());

				static util::Lookup<TextureMinFilter, GLenum> const k_lookup = {
					{ TextureMinFilter::kNearest, GL_NEAREST },
					{ TextureMinFilter::kLinear, GL_LINEAR },
					{ TextureMinFilter::kNearestMipmapNearest, GL_NEAREST_MIPMAP_NEAREST },
					{ TextureMinFilter::kNearestMipmapLinear, GL_NEAREST_MIPMAP_LINEAR },
					{ TextureMinFilter::kLinearMipmapNearest, GL_LINEAR_MIPMAP_NEAREST },
					{ TextureMinFilter::kLinearMipmapLinear, GL_LINEAR_MIPMAP_LINEAR }
				};

				bind();

				RE_OGL(glTexParameteri(get_target(m_type), GL_TEXTURE_MIN_FILTER, k_lookup[filter]));
			}

			void Texture::set_s_wrap(
				TextureWrap wrap)
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(graphics::Context::require());

				bind();
				RE_OGL(glTexParameteri(get_target(m_type), GL_TEXTURE_WRAP_S, get_wrap(wrap)));
			}

			void Texture::set_t_wrap(
				TextureWrap wrap)
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(graphics::Context::require());

				bind();
				RE_OGL(glTexParameteri(get_target(m_type), GL_TEXTURE_WRAP_T, get_wrap(wrap)));
			}

			void Texture::set_r_wrap(
				TextureWrap wrap)
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(graphics::Context::require());

				bind();
				RE_OGL(glTexParameteri(get_target(m_type), GL_TEXTURE_WRAP_R, get_wrap(wrap)));
			}

			void Texture::bind()
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(graphics::Context::require());

				if(!bound())
				{
					s_binding[type()].bind(handle());


					RE_OGL(glBindTexture(get_target(type()), handle()));
				}
			}

			void Texture1D::set_texels(
				Bitmap1D const& texels,
				uint_t lod)
			{
				RE_DBG_ASSERT(exists());

				bind();

				RE_OGL(glTexImage1D(
					GL_TEXTURE_1D,
					lod,
					get_internalformat(texels.channel()),
					texels.size(),
					0,
					get_format(texels.channel()),
					get_type(texels.component()),
					texels.data()));
			}

			uint_t Texture1D::set_texels_mipmap(
				Bitmap1D const& base_texels,
				MipmapFilter filter)
			{
				RE_DBG_ASSERT(RE_IN_ENUM(filter, MipmapFilter));
				RE_DBG_ASSERT(base_texels.exists());

				set_texels(base_texels, 0);
				Bitmap1D mip;
				if(base_texels.size() > 1)
				{
					mip = (filter == MipmapFilter::kNearest)
						? base_texels.create_mipmap_near()
						: base_texels.create_mipmap_lin();
					set_texels(mip, 1);

					uint_t lod = 1;
					while(mip.size() > 1)
					{
						mip = (filter == MipmapFilter::kNearest)
							? mip.create_mipmap_near()
							: mip.create_mipmap_lin();
						set_texels(mip, ++lod);
					}

					return lod;
				} else
					return 0;
			}

			void Texture1D::resize(
				uint_t size,
				Component component,
				Channel channel)
			{
				RE_DBG_ASSERT(exists());

				bind();

				RE_OGL(glTexImage1D(
					GL_TEXTURE_1D,
					0,
					get_internalformat(channel),
					size,
					0,
					get_format(channel),
					get_type(component),
					nullptr));

				m_size = size;
			}

			void Texture2D::set_texels(
				Bitmap2D const& texels,
				uint_t lod)
			{
				RE_DBG_ASSERT(exists());

				bind();

				RE_OGL(glTexImage2D(
					GL_TEXTURE_2D,
					lod,
					get_internalformat(texels.channel()),
					texels.width(),
					texels.height(),
					0,
					get_format(texels.channel()),
					get_type(texels.component()),
					texels.data()));
			}

			uint_t Texture2D::set_texels_mipmap(
				Bitmap2D const& base_texels,
				MipmapFilter filter)
			{
				RE_DBG_ASSERT(exists());
				RE_DBG_ASSERT(base_texels.exists());
				RE_DBG_ASSERT(RE_IN_ENUM(filter, MipmapFilter));

				bind();

				set_texels(base_texels, 0);
				Bitmap2D mip;
				if(base_texels.size() > 1)
				{
					mip = (filter == MipmapFilter::kNearest)
						? base_texels.create_mipmap_near()
						: base_texels.create_mipmap_lin();
					set_texels(mip, 1);

					uint_t lod = 1;
					while(mip.size() > 1)
					{
						mip = (filter == MipmapFilter::kNearest)
							? mip.create_mipmap_near()
							: mip.create_mipmap_lin();
						set_texels(mip, ++lod);
					}

					return lod;
				} else
					return 0;
			}

			void Texture2D::resize(
				uint_t width,
				uint_t height,
				Channel channel,
				Component component)
			{
				RE_DBG_ASSERT(exists());

				RE_DBG_ASSERT(width > 0);
				RE_DBG_ASSERT(height > 0);

				bind();

				m_width = width;
				m_height = height;

				uint_t lod = 0;
				while(width >= 1 && height >= 1)
				{
					RE_OGL(glTexImage2D(
						GL_TEXTURE_2D,
						lod++,
						get_internalformat(channel),
						width,
						height,
						0,
						get_format(channel),
						get_type(component),
						nullptr));

					width >>= 1;
					height >>= 1;
				}
			}

			void Texture3D::set_texels(
				Bitmap3D const& texels,
				uint_t lod)
			{
				RE_DBG_ASSERT(exists());

				bind();

				RE_OGL(glTexImage3D(
					GL_TEXTURE_3D,
					lod,
					get_internalformat(texels.channel()),
					texels.width(),
					texels.height(),
					texels.depth(),
					0,
					get_format(texels.channel()),
					get_type(texels.component()),
					texels.data()));

				m_width = texels.width();
				m_height = texels.height();
				m_depth = texels.depth();
			}
		}
	}
}