#ifndef __re_base_types_hpp_defined
#define __re_base_types_hpp_defined

#include <string>
#include <cstdint>
#include <cstddef>
#include "util/Argument.hpp"

namespace re
{
	typedef std::uint8_t ubyte_t, uint8_t;
	typedef std::int8_t byte_t, int8_t;

	typedef std::uint16_t uint16_t;
	typedef std::int16_t int16_t;

	typedef unsigned int uint_t;
	typedef std::uint32_t uint32_t;
	typedef std::int32_t int32_t;

	typedef std::size_t size_t;

	using util::copy_arg_t;
	using util::move_arg_t;
}

#endif