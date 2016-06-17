#ifndef __re_file_bmpfile_hpp_defined
#define __re_file_bmpfile_hpp_defined

#include "../types.hpp"
#include "../graphics/Bitmap.hpp"

namespace re
{
	namespace file
	{
		/** Loads a Bitmap from the given file. */
		bool loadBMP(char const* filename, Bitmap2D &out);
	}
}

#endif