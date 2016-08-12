/** @file Lookup.hpp
	Contains a neat class for creating lookup tables for enums. */
#ifndef __re_util_lookup_hpp_defined
#define __re_util_lookup_hpp_defined

#include "../defines.hpp"
#include <array>

namespace re
{
	namespace util
	{
		template<
			typename Enum,
			typename Target>
		class Lookup
		{
			std::array<Target, RE_COUNT(Enum)> m_values;
		public:
			Lookup() = default;
			RECXDA Lookup(
				std::array<
					std::pair<
						Enum,
						Target>,
					RE_COUNT(Enum)> values):
				m_values(values.second...)
			{
#ifdef RE_DEBUG
				for(size_t i = 0; i<RE_COUNT(Enum); i++)
					RE_DBG_ASSERT((values[i].first == (Enum) i
						&& "Invalid order of lookup table entries.");
#endif
			}

			RECXDA Target operator[](
				Enum index) const
			{
				RE_DBG_ASSERT(RE_IN_ENUM(index, Enum));
				return m_values[(size_t) index];
			}
		};
	}
}

#endif