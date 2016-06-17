#ifndef __re_string_hpp_defined
#define __re_string_hpp_defined

#include "defines.hpp"
#include "base_types.hpp"

namespace re
{

	typedef uint32_t utf32_t;
	typedef uint8_t utf8_t;

	template<class C>
	struct char_trait
	{
		static_assert(false, "character type not supported.");
	};

	typedef<class C>
	/** String class. To be a replacement for the std::string class, and have some extensions, for example type safe formatting functions. */
	class String
	{
		C const * m_ptr;
		size_t m_size;
		size_t m_capacity;
	public:

		String();
		String(NotNull<C const> ptr);
		String(String<C> const& copy);
		String(String<C> && move);

		String<C> &operator=(NotNull<C const> * ptr);
		String<C> &operator=(String<C> const& copy);
		String<C> &operator=(String<C> && move);

		bool operator==(String<C> const& rhs) const;
		bool operator==(NotNull<C> const& rhs) const;

		/** Returns whether the string is empty or uninitialized. */
		RECX bool empty() const;

		/** The amount of elements in the string. */
		RECX size_t size() const;
		/** For UTF-8 strings, O = O(n), and represents the amount of characters represented in the string. For UTF-32 strings, acts the same as size(). */
		RECX size_t characters() const;
		/** The string data - this is guaranteed to be a valid pointer. If the string is empty, returns a statically allocated pointer. */
		RECX NotNull<C const> data() const;
		/** The number of elements allocated. */
		RECX size_t capacity() const;

		/** Transforms the string into an upper case string. */
		String<C> &make_upper();

		/** Transformst the string into a lower case string. */
		String<C> &make_lower();

		/** Reserves the given count of */
		void reserve(size_t capacity);
		/** Empties the string. */
		void clear();
	};

	typedef String<utf32_t> Utf32String;
	typedef String<utf8_t> Utf8String;
}

#endif