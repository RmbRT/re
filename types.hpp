#ifndef __re_types_hpp_defined
#define __re_types_hpp_defined

#include "defines.hpp"
#include "LogFile.hpp"
#include "base_types.hpp"

#include "util/Lazy.hpp"
#include "util/NotNull.hpp"
#include "util/MemoryPool.hpp"
#include "util/Delegate.hpp"
#include <lock/Lock.hpp>

namespace re
{
	using re::util::lazy;
	using re::util::notnull;
	using re::util::unsafe;

	using re::util::strong_handle;
	using re::util::weak_handle;
	using re::util::unique_handle;
	
	using re::util::Delegate;


	using re::util::alloc;

	using re::util::dynamic;
	using re::util::cast;
	using re::util::reinterpret;
}

#endif