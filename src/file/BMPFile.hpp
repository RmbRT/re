#ifndef __re_file_bmpfile_hpp_defined
#define __re_file_bmpfile_hpp_defined

#include "../types.hpp"
#include "../graphics/Bitmap.hpp"

namespace re
{
	namespace file
	{
		/** Loads a Bitmap from the given file.
			The file must be a bitmap file. The data is stored in the out parameter, if the file was loaded successfully.
		@param[in] filename:
			The name of the bitmap file that is to be loaded.
		@param[out] out:
			The data contained in the file.
		@return
			Whether the file was successfully loaded. */
		bool load_bmp(char const* filename, graphics::Bitmap2D &out);
	}
}

#endif