#ifndef __re_base_types_hpp_defined
#define __re_base_types_hpp_defined

#include <string>
#include <cstdint>
#include "util/Argument.hpp"

namespace re
{
	typedef unsigned char uchar;
	typedef std::uint8_t ubyte, uint8;
	typedef std::int8_t byte, int8;
	typedef unsigned short ushort;
	typedef std::uint16_t uword, uint16;
	typedef std::int8_t word, int16;
	typedef unsigned int uint;
	typedef std::uint32_t udword, uint32;
	typedef std::int32_t dword, int32;
	typedef std::size_t size_t;

	using std::string;
	using std::wstring;

	using std::u16string;
	using std::u32string;

	using util::copy_arg_t;
	using util::move_arg_t;
}

#endif