#ifndef __re_string_hpp_defined
#define __re_string_hpp_defined

#include "defines.hpp"
#include "base_types.hpp"
#include "util/NotNull.hpp"
#include "util/Pointer.hpp"

namespace re
{

	/** UTF-32 character. */
	typedef uint32_t utf32_t;
	/** UTF-8 character. */
	typedef uint8_t utf8_t;

	using util::NotNull;
	using util::Auto;

	template<class C>
	/** String class. To be a replacement for the std::string class, and have some extensions, for example type safe formatting functions. */
	class String
	{
		static C const s_empty;

		/** The character data of the string. */
		util::Auto<C []> m_data;
		/** The character count that is currently used. */
		size_t m_size;
		/** The current amount of characters allocated. */
		size_t m_capacity;
	public:
		/** Creates an empty string. */
		RECX String();
		/** Creates a string holding a copy of the given string.
		@param[in] ptr:
			The string to copy.
			The string must be null-terminated. */
		String(
			NotNull<C const> ptr);
		/** Creates a string holding a copy of the given string.
		@param[in] copy:
			The string to copy. */
		String(
			String<C> const& copy);
		/** Moves a string to another instance.
			The argument will give up ownership of its data.
		@param[in] move:
			The string to move from. */
		String(
			String<C> && move);

		/** Copies the given string into this string.
		@param[in] ptr:
			The string to copy from.
			The string must be null-terminated.
			@assert
				Must not be this string. */
		String<C> &operator=(
			NotNull<C const> ptr);
		/** Copies the given string into this string.
		@param[in] copy:
			The string to copy from.
			@assert
				Must not be this string. */
		String<C> &operator=(
			String<C> const& copy);
		/** Moves the given string into this string.
		@param[in] move:
			The string to move from.
			@assert
				Must not be this string. */
		String<C> &operator=(
			String<C> && move);

		/** Compares this string to the given string.
		@param[in] rhs:
			The string to compare to this string. */
		bool operator==(
			String<C> const& rhs) const;
		/** Compares this string to the given string.
		@param[in] rhs:
			The string to compare to this string.
			The string must be null-terminated. */
		bool operator==(
			NotNull<C const> rhs) const;

		/** Returns whether the string is empty or uninitialized. */
		REIL bool empty() const;

		/** The amount of elements in the string.
			This might not be the number of characters represented by the string, see length(). */
		REIL size_t size() const;
		/** Returns the number of characters represented by this string.
			For UTF-8 strings, this matches the number of unicode code points encoded in the string, and not necessarily the number of elements, so for UTF-8 strings this has linear complexity. For UTF-32 strings this is equivalent to size(). */
		REIL size_t length() const;
		/** The string data - might be null. */
		REIL C const * data() const;
		REIL C * data();
		/** The string contents.
			If the string is null, an empty string is returned.*/
		REIL NotNull<C const> content() const;
		/** The number of elements allocated. */
		REIL size_t capacity() const;

		/** Reserves the given count of elements.
			If the current capacity is greater than the requested capacity, does nothing.
		@param[in] capacity:
			The minimal amount of elements to allocate. */
		void reserve(
			size_t capacity);

		/** Resizes the string to hold the requested amount of elements.
			If the current size is less than the requested size, a null-terminator is put at the old end of the string. If the current size is greater than the requested size, a null-terminator is put at the new end of the string. 
		@param[in] size:
			The new element count of the string (not including null-terminator). */
		void resize(
			size_t size);

		/** Empties the string. */
		void clear();
	};

	typedef String<utf32_t> Utf32String;
	typedef String<utf8_t> Utf8String;
}

#include "String.inl"

#endif