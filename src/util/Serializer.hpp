#ifndef __re_util_serializer_hpp_defined
#define __re_util_serializer_hpp_defined

#include <vector>
#include "../types.hpp"

namespace re
{
	namespace util
	{

		class Serializer
		{
			friend class SerializableBase;

			uint64_t m_target_byte_order;
			std::vector<byte_t> m_data;

			REIL void append(byte_t byte);

		public:
			RECX Serializer();
			REIL byte_t const * data() const;
		};
		/** Permission hook for friend to template. */
		class Serializable
		{
		public:
			virtual void serialize(Serializer & serializer) = 0;
		};
	}
}

#endif