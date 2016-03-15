#ifndef __re_graphics_gl_texture_hpp_defined
#define __re_graphics_gl_texture_hpp_defined

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

			public:
				using Handle::handle;
				using Handle::exists;

				void imageData(Bitmap const& data);
			};
		}
	}
}

#endif