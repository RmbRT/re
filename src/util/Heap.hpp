#ifndef __re_util_heap_hpp_defined
#define __re_util_heap_hpp_defined

#include "../defines.hpp"
#include "../types.hpp"

#ifdef RE_DEBUG
/** Define this to prevent the heap checks from being performed. */
#ifndef RE_HEAP_NODEBUG
	/** Defined when heap checks should be performed. */
	#define RE_HEAP_DEBUG
#endif
#endif

namespace re
{
	REIL void * alloc(size_t size);
	REIL void free(void const * mem);
	REIL bool resize(void const * memory, size_t size);
	REIL void * realloc(void const * memory, size_t size);

	namespace util
	{
		/** Custom Heap class.
			The Heap, once allocated, cannot be resized, except via deallocating and reallocating. */
		class Heap
		{
#ifdef RE_HEAP_DEBUG
			/** feffefee for 32 bit, babbabaafeffefee for 64 bit. */
			size_t const heap_magic = ((size_t(0xbabbabaa) << 32) | size_t(0xfeffefee))
#endif

			/** The Header structure that describes a block of allocated memory. */
			struct Header
			{
#ifdef RE_HEAP_DEBUG
				size_t m_magic;
#endif
				/** The previous Header, or null if none. */
				Header * m_prev;
				/** The heap this Header belongs to.
					This is used to allow the existence of multiple Heaps, where the deleter function does not have to know what heap a memory block is allocated from. */
				Heap * m_heap;
				/** The bytes allocated in this header. */
				size_t m_size;
				/** The next used header. */
				Header * m_next;

				void free();

				/** The*/
				RECX size_t capacity() const;
				/** The size of the hole between this one and the next one. */
				RECX size_t hole() const;
				RECX uintptr_t end() const;
			};

			/** The allocated memory of the Heap. */
			Header * m_pool;
			/** The capacity of the heap. */
			size_t m_capacity;
			/** The first allocated memory block of the Heap. */
			Header * m_first;
			/** The last allocated memory block of the Heap. */
			Header * m_last;

			/** The first address that is outside the Heap. */
			RECXDA uintptr_t end() const;
			/** In RE_HEAP_DEBUG, checks for valid address position. */
			RECX bool isValidHeaderAddress(Header const * header) const;

			/** In RE_HEAP_DEBUG, validates the header and its pointers. */
			RECXDA void validateHeader(Header const * header) const;

		public:
			/** Unallocated Heap. */
			Heap();
			/** Heap with given capacity. */
			explicit Heap(size_t capacity);
			Heap(Heap &&);
			Heap &operator=(Heap &&);
			~Heap();

			/** Attempts to resize the allocated memory.
			@return Whether the memory could be resized without moving it. */
			bool resize(void const * mem, size_t size);
			/** If the memory cannot be resized, it will be copied to a newly allocated destination. */
			void * realloc(void const * mem, size_t size);
			/** Allocates memory. */
			void * alloc(size_t size);

			/** Whether the memory pool is allocated. */
			RECX bool exists() const;
			/** Whether there are allocated blocks within the Heap. */
			RECX bool used() const;

			/** Allocates the Heap. */
			void create(size_t capcity);
			/** Deallocates the Heap. */
			void dealloc();


			/** Returns the Header address that belongs to the beginning of a memory block. */
			static RECX Header * getHeader(void const * membegin);
		private:
			/** Invalidates the Heap (for moving). */
			void invalidate();

			Heap(Heap const&) = default;
			Heap &operator=(Heap const&) = default;
		};
	}
}

#endif