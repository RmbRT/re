#ifndef __re_file_bmpfile_hpp_defined
#define __re_file_bmpfile_hpp_defined

#include "../types.hpp"
#include "../graphics/Bitmap.hpp"
#include <fstream>
namespace re
{
	namespace file
	{
		graphics::Bitmap loadBMP(const std::string &file);
	}
}

#endif