#ifndef __re_texture_hpp_defined
#define __re_texture_hpp_defined

#include "../types.hpp"
#include "../defines.hpp"
#include "../math/Vector.hpp"
#include "Bitmap.hpp"

namespace re
{
	namespace graphics
	{
		
		/*Used for coniguring the parameters of a Texture.*/
		RE_ENUM(Filter)
		{
			F_NEAREST,
			F_LINEAR,
			F_NEAREST_MIPMAP_LINEAR,
			F_NEAREST_MIPMAP_NEAREST,
			F_LINEAR_MIPMAP_LINEAR,
			F_LINEAR_MIPMAP_NEAREST
		};
		/*Used for coniguring the parameters of a Texture.*/
		RE_ENUM(Wrap)
		{
			W_CLAMP,
			W_REPEAT,
			W_CLAMP_TO_BORDER,
			W_CLAMP_TO_EDGE,
			W_MIRRORED_REPEAT
		};
		/*Used for coniguring the parameters of a Texture.*/
		RE_ENUM(TextureCompareMode)
		{
			COMPARE_R_TO_TEXTURE,
			NONE
		};
		/*Used for coniguring the parameters of a Texture.*/
		RE_ENUM(TextureCompareFunc)
		{
			LEQUAL,
			GEQUAL,
			LESS,
			GREATER,
			EQUAL,
			NOTEQUAL,
			ALWAYS,
			NEVER
		};
		/*Used for coniguring the parameters of a Texture.*/
		RE_ENUM(DepthTextureMode)
		{
			LUMINANCE,
			INTESITY,
			ALPHA
		};

		/*Contains the parameters of a Texture as used by OpenGL.*/
		struct TextureParameters
		{
			/*Constructs TextureParameters with the default OpenGL values.*/
			TextureParameters();
			/*The min and mag Texture Filter.*/
			Filter min_filter, mag_filter;
			/*The texture wrap mode.*/
			Wrap wrap_s, wrap_t, wrap_r;
			/*The min and max LOD values for this Texture.*/
			float min_lod, max_lod;
			/*The base and max level.*/
			int32 base_level, max_level;
			math::fvec4 border_color;
			float priority;
			TextureCompareMode compare_mode;
			TextureCompareFunc compare_func;
			DepthTextureMode depth_texture_mode;
			bool generate_mipmap;
		};


		/*Describes a Texture as used by OpenGL.*/
		class Texture
		{
			uint32 id;
			uint8 dimension;
			uint32 width, height, depth;
			TextureParameters parameters;
			Bitmap data;
			std::vector<Bitmap> mipmaps;
		public:
			/*Creates a Texture object. This does not allocate memory on the GPU.*/
			Texture();
			/*Moves a Texture object into a new instance and invalidates the old one.*/
			Texture(Texture &&move);
			/*Moves a Texture object into a new instance and invalidates the old one.*/
			Texture &operator=(Texture &&move);
			/*Destroys the Texture. Also frees all the memory allocated on the GPU by it.*/
			~Texture();
			/*Allocates a Texture handle to the GPU.
			@param[in] dimension: The dimension of the texture (1 for 1D, 2 for 2D).*/
			void alloc(uint8 dimension);
			/*To prevent memory leaks, call this function. This deletes the used memory on the GPU.*/
			void destroy();

			/*Binds the Texture to the rendering pipeline.*/
			void bind() const;
			/*Unbinds the currently bound Texture.*/
			static void unbind();

			/*Checks whether the Texture has valid id.*/
			bool exists() const;
			void reload() const;
			void reloadIfNotExist();

			/*Returns whether this Texture is currently bound to the rendering pipeline.*/
			bool isBound() const;
			/*Returns the width of the Texture in pixels.*/
			uint32 getWidth() const;
			/*Returns the height of the Texture in pixels.*/
			uint32 getHeight() const;
			/*Returns the depth of the Texture in pixels.*/
			uint32 getDepth() const;

			uint32 getId() const;

			/*Returns the dimension of the Texture.*/
			uint8 getDimension() const;

			/*Passes all the parameters of the texture to the GPU.*/
			void updateParameters() const;

			/*Returns the parameters of this Texture.*/
			TextureParameters &getParameters();
			/*Returns the parameters of this Texture.*/
			const TextureParameters &getParameters() const;
			
			void setData(const Bitmap &);

			/*Sets the bounds of the Texture. The content of the texture is empty.*/
			void setBounds(uint width, uint height);
			/*Calculates and uploads the mipmaps for this Texture.
			@param[in] filter: the MipMap generation filter.
			This overrides all MipMaps currently held by this Texture, other than the base MipMap.*/
			void generateMipMaps(MipmapFilter filter, int maxLevel);

		private:
			/*Loads the mipmap level <level> onto the gpu.
			@param[in] Bitmap: the image data of the mipmap.
			@param[in] level: the level of the mipmap. 0 for the base image.
			This function does not override the stored mipmaps in the Texture class.*/
			void _setTexImage(const Bitmap &, size_t level) const;

			/*The currently bound texture. This is used to reduce redundant calls to the GPU.*/
			static uint32 bound;
		};
	}
}


#endif