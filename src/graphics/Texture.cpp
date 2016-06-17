#include "Texture.hpp"
#include "OpenGL.hpp"

#include "../LogFile.hpp"
#include "../modules/GLObjectManager.hpp"

re::uint32 re::graphics::Texture::bound = 0;

namespace re
{
	namespace graphics
	{

		inline GLenum textureType(uint8 dimension)
		{
			switch(dimension)
			{
			case 1:
				{
					return GL_TEXTURE_1D;
				} break;
			case 2:
				{
					return GL_TEXTURE_2D;
				} break;
			default:
				{
					RE_LOG("Invalid Texture Dimension %i", (int)dimension);
					//return GL_TEXTURE_3D;
				} break;
			}
		}

		Texture::Texture(): id(0), dimension(2), width(0), height(0), depth(0), parameters(), data()	{	}
		Texture::~Texture()
		{
			destroy();
		}

		Texture::Texture(Texture &&move): id(move.id), dimension(move.dimension), width(move.width), height(move.height), depth(move.depth), parameters(move.parameters), data(std::move(move.data)) { move.id = 0; move.dimension = move.width = move.height = 0; }

		Texture &Texture::operator=(Texture &&move)
		{
			if(this == &move)
				return *this;
			destroy();

			id = move.id;
			dimension = move.dimension;
			width = move.width;
			height = move.height;
			depth = move.depth;
			parameters = move.parameters;
			data = std::move(move.data);
			move.id = 0;
			move.dimension = move.width = move.height = move.depth = 0;
		}

		void Texture::alloc(uint8 dimension)
		{
			destroy();
			this->dimension = dimension;
			RE_OGL(glGenTextures(1, &id));
			LogFile::GetInst()->writefln("%i",glGetError());
			RE_ASSERT(id);
			modules::GLObjectManager::GetInst()->onAlloc(this, id);
			bind();
		}

		void Texture::destroy()
		{
			if(!id)
				return;

			RE_LOG("DESTROY TEX %i", id);

			modules::GLObjectManager::GetInst()->onDestroy(this, id);

			if(isBound())
				unbind();
			RE_OGL(glDeleteTextures(1, &id));
			id = 0;
			width = 0;
			height = 0;
			dimension = 2;
			parameters = TextureParameters();
		}
		void Texture::bind() const
		{
			if(isBound())
				return;
			RE_OGL("Previous Error");

			GLenum target;
			switch(dimension)
			{
			case 1:
				{
					target = GL_TEXTURE_1D;
				} break;
			case 2:
				{
					target = GL_TEXTURE_2D;
				} break;
			//case 3:
			//	{
			//		target = GL_TEXTURE_3D;
			//	} break;
			default:
				{
					LogFile::GetInst()->writefln("Texture %i @%x (%ux%u) has invalid dimension %i!", id, this, width, height, dimension);
				} break;

			}
			RE_OGL(glBindTexture(target, id));
			bound = id;
		}

		bool Texture::isBound() const
		{
			if(!bound)
				return false;
			return bound == id;
		}

		void Texture::unbind()
		{
			if(bound)
			{
				RE_OGL(glBindTexture(GL_TEXTURE_2D, 0));
				bound = 0;
			}
		}

		bool Texture::exists() const
		{
			GLboolean is;
			RE_OGL((is = glIsTexture(id)));
			RE_LOG("Checking for Texture %i: %s", id, is?"true":"false");
			return is;
		}

		void Texture::reload() const
		{
			RE_ASSERT(id);
			bind();
			updateParameters();
			_setTexImage(data,0);
			for(size_t level = 0; level < mipmaps.size();)
				_setTexImage(mipmaps[level], ++level);
		}
		void Texture::reloadIfNotExist()
		{
			if(!exists())
			{
				alloc(2);
				reload();
			}
		}

		uint32 Texture::getWidth() const
		{
			return width;
		}

		uint32 Texture::getHeight() const
		{
			return height;
		}

		uint32 Texture::getDepth() const
		{
			return depth;
		}

		uint32 Texture::getId() const
		{
			return id;
		}

		uint8 Texture::getDimension() const
		{
			return dimension;
		}

		inline GLenum getGLenum(Filter filter)
		{
			switch(filter)
			{
			case Filter::F_LINEAR:
				{
					return GL_LINEAR;
				} break;
			case Filter::F_LINEAR_MIPMAP_LINEAR:
				{
					return GL_LINEAR_MIPMAP_LINEAR;
				} break;
			case Filter::F_LINEAR_MIPMAP_NEAREST:
				{
					return GL_LINEAR_MIPMAP_NEAREST;
				} break;
			case Filter::F_NEAREST:
				{
					return GL_NEAREST;
				} break;
			case Filter::F_NEAREST_MIPMAP_LINEAR:
				{
					return GL_NEAREST_MIPMAP_LINEAR;
				} break;
			case Filter::F_NEAREST_MIPMAP_NEAREST:
				{
					return GL_NEAREST_MIPMAP_NEAREST;
				} break;
			default:
				RE_ASSERTION_FAILURE("Invalid enum value passed.");
				break;
			}
		}

		inline GLenum getGLenum(TextureCompareMode compare_mode)
		{
			switch(compare_mode)
			{
			case TextureCompareMode::COMPARE_R_TO_TEXTURE:
				{
					return GL_COMPARE_R_TO_TEXTURE;
				} break;
			case TextureCompareMode::NONE:
				{
					return GL_NONE;
				} break;
			default:
				RE_ASSERTION_FAILURE("");
				break;
			}
		}

		inline GLenum getGLenum(TextureCompareFunc compare_func)
		{
			switch(compare_func)
			{
			case TextureCompareFunc::ALWAYS:
				{
					return GL_ALWAYS;
				} break;
			case TextureCompareFunc::EQUAL:
				{
					return GL_EQUAL;
				} break;
			case TextureCompareFunc::GEQUAL:
				{
					return GL_GEQUAL;
				} break;
			case TextureCompareFunc::GREATER:
				{
					return GL_GREATER;
				} break;
			case TextureCompareFunc::LEQUAL:
				{
					return GL_LEQUAL;
				} break;
			case TextureCompareFunc::LESS:
				{
					return GL_LESS;
				} break;
			case TextureCompareFunc::NEVER:
				{
					return GL_NEVER;
				} break;
			case TextureCompareFunc::NOTEQUAL:
				{
					return GL_NOTEQUAL;
				} break;
			default:
				RE_ASSERTION_FAILURE("");
				break;
			}
		}

		inline GLenum getGLenum(DepthTextureMode depth_texture_mode)
		{
			switch(depth_texture_mode)
			{
			case DepthTextureMode::ALPHA:
				{
					return GL_ALPHA;
				} break;
			case DepthTextureMode::INTESITY:
				{
					return GL_INTENSITY;
				} break;
			case DepthTextureMode::LUMINANCE:
				{
					return GL_LUMINANCE;
				} break;
			default:
				RE_ASSERTION_FAILURE("");
				break;
			}
		}

		inline GLenum getGLenum(Wrap wrap)
		{
			switch(wrap)
			{
			case Wrap::W_CLAMP:
				{
					return GL_CLAMP;
				} break;
			case Wrap::W_CLAMP_TO_BORDER:
				{
					return GL_CLAMP_TO_BORDER;
				} break;
			case Wrap::W_CLAMP_TO_EDGE:
				{
					return GL_CLAMP_TO_EDGE;
				} break;
			case Wrap::W_MIRRORED_REPEAT:
				{
					return GL_MIRRORED_REPEAT;
				} break;
			case Wrap::W_REPEAT:
				{
					return GL_REPEAT;
				} break;
			default:
				RE_ASSERTION_FAILURE("");
				break;
			}
		}

		void Texture::updateParameters() const
		{
			RE_OGL(bind());

			GLenum target = textureType(dimension);

			LogFile::GetInst()->writefln("%i (%x)", target, target);
			LogFile::GetInst()->flush();
			Filter mag_filter;
			switch(parameters.mag_filter)
			{
			case Filter::F_LINEAR:
			case Filter::F_LINEAR_MIPMAP_LINEAR:
			case Filter::F_LINEAR_MIPMAP_NEAREST:
				{
					mag_filter = Filter::F_LINEAR;
				} break;
			case Filter::F_NEAREST:
			case Filter::F_NEAREST_MIPMAP_LINEAR:
			case Filter::F_NEAREST_MIPMAP_NEAREST:
			default:
				{
					mag_filter = Filter::F_NEAREST;
				} break;
			}

			RE_OGL(glTexParameteri(target, GL_TEXTURE_WRAP_S, getGLenum(parameters.wrap_s)));
			RE_OGL(glTexParameteri(target, GL_TEXTURE_WRAP_T, getGLenum(parameters.wrap_t)));
			RE_OGL(glTexParameteri(target, GL_TEXTURE_WRAP_R, getGLenum(parameters.wrap_r)));

			RE_OGL(glTexParameteri(target, GL_TEXTURE_MIN_FILTER, getGLenum(parameters.min_filter)));
			RE_OGL(glTexParameteri(target, GL_TEXTURE_MAG_FILTER, getGLenum(mag_filter)));

			RE_OGL(glTexParameterf(target, GL_TEXTURE_MIN_LOD, parameters.min_lod));
			RE_OGL(glTexParameterf(target, GL_TEXTURE_MAX_LOD, parameters.max_lod));

			RE_OGL(glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, parameters.base_level));
			RE_OGL(glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, parameters.max_level));

			RE_OGL(glTexParameterfv(target, GL_TEXTURE_BORDER_COLOR, parameters.border_color));
			
			RE_OGL(glTexParameteri(target, GL_TEXTURE_COMPARE_MODE, getGLenum(parameters.compare_mode)));
			RE_OGL(glTexParameteri(target, GL_TEXTURE_COMPARE_FUNC, getGLenum(parameters.compare_func)));
		}


		TextureParameters &Texture::getParameters()
		{
			return parameters;
		}

		const TextureParameters &Texture::getParameters() const
		{
			return parameters;
		}

		TextureParameters::TextureParameters() : min_filter(Filter::F_LINEAR), mag_filter(Filter::F_LINEAR),
			wrap_s(Wrap::W_REPEAT), wrap_t(Wrap::W_REPEAT), wrap_r(Wrap::W_REPEAT),
			min_lod(-1000.f), max_lod(1000.f),
			base_level(0), max_level(1000),
			border_color(0,0,0,0),
			priority(0.5f),
			compare_mode(TextureCompareMode::NONE),
			compare_func(TextureCompareFunc::GREATER),
			depth_texture_mode(DepthTextureMode::LUMINANCE),
			generate_mipmap(false)	{	}

		void Texture::_setTexImage(const Bitmap &bmp, size_t level) const
		{
			GLint internalFormat = GL_INVALID_ENUM;
			GLint type = GL_INVALID_ENUM;
			GLint format = GL_INVALID_ENUM;
			switch(bmp.getChannel())
			{
			case ColorChannel::FLOAT1:	{	internalFormat = GL_R; type = GL_FLOAT; format = GL_LUMINANCE;		} break;
			case ColorChannel::BYTE1:	{	internalFormat = GL_R; type = GL_UNSIGNED_BYTE; format = GL_LUMINANCE;	} break;
			case ColorChannel::FLOAT2:	{	internalFormat = GL_RG; type = GL_FLOAT; format = GL_LUMINANCE_ALPHA;} break;
			case ColorChannel::BYTE2:	{	internalFormat = GL_RG; type = GL_UNSIGNED_BYTE; format = GL_LUMINANCE_ALPHA;} break;
			case ColorChannel::FLOAT3:	{	internalFormat = GL_RGB; type = GL_FLOAT; format = GL_RGB; } break;
			case ColorChannel::BYTE3:	{	internalFormat = GL_RGB; type = GL_UNSIGNED_BYTE; format = GL_RGB; } break;
			case ColorChannel::FLOAT4:	{	internalFormat = GL_RGBA; type = GL_FLOAT; format = GL_RGBA; } break;
			case ColorChannel::BYTE4:	{	internalFormat = GL_RGBA; type = GL_UNSIGNED_BYTE; format = GL_RGBA; } break;
			}

			bind();
			if(dimension==1)
			{
				RE_OGL(glTexImage1D(GL_TEXTURE_1D, level, internalFormat, bmp.getWidth(), 0, format, type, bmp.getBaseAddress()));
			}
			else if(dimension==2)
			{
				RE_OGL(glTexImage2D(GL_TEXTURE_2D, level, internalFormat, bmp.getWidth(), bmp.getHeight(), 0, format, type, bmp.getBaseAddress()));
			}
			else
			{
				LogFile::GetInst()->writefln(__FUNCTION__" Unsupported texture dimension %i", dimension);
			}
		}

		void Texture::setData(const Bitmap &bmp)
		{
			if(!id)
				alloc(2);
			data = bmp;
			width = bmp.getWidth();
			height = bmp.getHeight();
			dimension = 2;

			_setTexImage(bmp, 0);
		}

		void Texture::setBounds(uint width, uint height)
		{
			if(this->width == width && this->height == height)
				return;

			RE_LOG("(%i, %i)", width, height);

			bind();
			if(dimension == 1)
			{
				if(width==1)
					width = height;
				height = 1;
				this->width = width;
				this->height = height;

				RE_OGL(glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, width, 0, GL_RGBA, GL_FLOAT, Bitmap(ColorChannel::FLOAT4, width, height).getBaseAddress()));
			}
			else if(dimension == 2)
			{
				RE_OGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, Bitmap(ColorChannel::FLOAT4, width, height).getBaseAddress()));
			} else
			{
				LogFile::GetInst()->writefln(__FUNCTION__" Unsupported texture dimension %i", dimension);
			}
		}

		void Texture::generateMipMaps(MipmapFilter filter, int maxLevel)
		{
			mipmaps.clear();
			int level = 1;
			while((data.getWidth()>>level) && (data.getHeight()>>level) && (maxLevel!=level++))
				mipmaps.push_back(((level-2)?mipmaps.back() : data).generateMipMap(filter));
			switch(dimension)
			{
			case 1:
				RE_OGL(glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAX_LEVEL, mipmaps.size())); break;
			case 2:
				RE_OGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipmaps.size())); break;
			case 3:
				RE_OGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipmaps.size())); break;
			default:
				RE_ASSERTION_FAILURE("Texture dimension invalid.");
			}
			for(level = 0; level < mipmaps.size(); level++)
				_setTexImage(mipmaps[level], level+1);
		}

	}
}