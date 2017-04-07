#ifndef __re_util_heap_hpp_defined
#define __re_util_heap_hpp_defined

#include "../defines.hpp"
#include "../base_types.hpp"

#ifdef RE_DEBUG
/** Define this to prevent the heap checks from being performed. */
#ifndef RE_HEAP_NODEBUG
	/** Defined when heap checks should be performed. */
	#define RE_HEAP_DEBUG
#endif
#endif

namespace re
{
	REIL void * malloc(size_t size);
	REIL void free(void const * mem);
	REIL bool resize(void const * memory, size_t size);
	REIL void * realloc(void const * memory, size_t size);

	template<class T, class ... Args>
	REIL T * alloc(Args && ...);

	template<class T>
	REIL T * array_alloc(size_t count);

	template<class T>
	REIL void dealloc(T * ptr);

	template<class T>
	REIL void array_dealloc(T * ptr);

	namespace util
	{
		/** Custom Heap class.
			The Heap, once allocated, cannot be resized, except via deallocating and reallocating. */
		class Heap
		{
#ifdef RE_HEAP_DEBUG
			/** 0xfeffefee for 32 bit, 0xbabbabaafeffefee for 64 bit. */
			static size_t const heap_magic = ((size_t(0xbabbabaa) << 32) | size_t(0xfeffefee))
#endif
public:
			struct Header;
private:
			/** The allocated memory of the Heap. */
			Header * m_pool;
			/** The capacity of the heap. */
			size_t m_capacity;
			/** The first allocated memory block of the Heap. */
			Header * m_first;
			/** The last allocated memory block of the Heap. */
			Header * m_last;

			/** The first address that is outside the Heap. */
			REIL uintptr_t end() const;
			/** In RE_HEAP_DEBUG, checks for valid address position. */
			REIL bool is_valid_header_address(Header const * header) const;
		public:
			/** Unallocated Heap. */
			Heap();
			/** Heap with given capacity. */
			explicit Heap(size_t capacity);
			Heap(Heap &&);
			Heap &operator=(Heap &&);
			~Heap();

			/** Attempts to resize the allocated memory.
				The resizing will be successful if the current memory block can be resized without overlapping another existing memory block or going out of the bounds of the Heap. If it fails, the memory block pertains its size, otherwise it is resized.
			@return
				Whether the resizing was successful. */
			bool resize(void const * mem, size_t size);
			/** If the memory cannot be resized, it will be copied to a newly allocated destination. */
			void * realloc(void const * mem, size_t size);
			/** Allocates memory. */
			void * malloc(size_t size);

			template<class T, class ... Args>
			/** Allocates and constructs an instance of the requested type.
			@param[in] args:
				The arguments to be used when constructing the allocated instance. */
			REIL T * alloc(Args && ... args);

			template<class T>
			/** Allocates and constructs an array of the requested type and size.
				Each object in the array will be default constructed.
			@parmam[in] size:
				The element count of the array.
			@return
				The allocated array or null. */
			REIL T * array_alloc(size_t size);

			/** Whether the memory pool is allocated. */
			REIL bool exists() const;
			/** Whether there are allocated blocks within the Heap. */
			REIL bool used() const;

			/** Allocates the Heap. */
			void create(size_t capcity);
			/** Deallocates the Heap. */
			void dealloc();


			/** Returns the Header address that belongs to the beginning of a memory block. */
			static RECX Header * get_header(void const * membegin);

			/** In RE_HEAP_DEBUG, validates the header and its pointers. */
			REIL void validate_header(Header const * header) const;

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
				bool resize(size_t size);
				void * realloc(size_t size);
				/** The capacity of the memory block. */
				REIL size_t capacity() const;
				/** The size of the hole between this one and the next one. */
				REIL size_t hole() const;
				REIL uintptr_t end() const;
			};

		private:
			/** Invalidates the Heap (for moving). */
			void invalidate();

			Heap(Heap const&) = default;
			Heap &operator=(Heap const&) = default;
		};
	}
}

#include "Heap.inl"

#endif