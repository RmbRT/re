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
			REIL Lookup(
				std::array<
					std::pair<
						Enum,
						Target>,
					RE_COUNT(Enum)> values):
				m_values()
			{
#ifdef RE_DEBUG
				for(size_t i = 0; i<RE_COUNT(Enum); i++)
					RE_DBG_ASSERT((values[i].first == (Enum) i
						&& "Invalid order of lookup table entries.");
#endif

				for(size_t i = 0; i < m_values.size(); i++)
					m_values[i] = std::move(values[i].second);
			}

			REIL Lookup(
				std::initializer_list<
					std::pair<
						Enum,
						Target>> values):
				m_values()
			{
				RE_DBG_ASSERT(values.size() == RE_COUNT(Enum));

#ifdef RE_DEBUG
				for(size_t i = 0; i<RE_COUNT(Enum); i++)
					RE_DBG_ASSERT((values[i].first == (Enum) i
						&& "Invalid order of lookup table entries.");
#endif

				for(size_t i = 0; i < m_values.size(); i++)
					m_values[i] = std::move((values.begin()+i)->second);
			}

			REIL Target & operator[](
				Enum index)
			{
				RE_DBG_ASSERT(RE_IN_ENUM(index, Enum));
				return m_values[(size_t) index];
			}

			REIL Target const& operator[](
				Enum index) const
			{
				RE_DBG_ASSERT(RE_IN_ENUM(index, Enum));
				return m_values[(size_t) index];
			}
		};
	}
}

#endif
