#ifndef __re_file_bmpfile_hpp_defined
#define __re_file_bmpfile_hpp_defined

#include "../types.hpp"
#include "../graphics/Bitmap.hpp"
#include <fstream>

namespace re
{
	namespace file
	{
		/** Loads a Bitmap from the given file stream. */
		graphics::Bitmap loadBMP(std::ifstream &in);
	}
}

#endif