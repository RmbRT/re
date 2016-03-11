namespace re
{
	namespace util
	{
		
		template<class T, class ...Args>
		REINL unique_handle<T> alloc(Args&&... args)
		{
			return MemoryPool<T>::GetInst()->alloc(std::forward<Args>(args)...);
		}
		
		template<class T, class U>
		REINL strong_handle<T> dynamic(const strong_handle<U> &handle)
		{
			return handle.dynamic_handle_cast<T>();
		}

		template<class T, class U>
		REINL strong_handle<T> cast(const strong_handle<U> &handle)
		{
			return handle.static_handle_cast<T>();
		}
	
		template<class T, class U>
		REINL weak_handle<T> dynamic(const weak_handle<U> &handle)
		{
			return handle.dynamic_handle_cast<T>();
		}

		template<class T, class U>
		REINL weak_handle<T> cast(const weak_handle<U> &handle)
		{
			return handle.static_handle_cast<T>();
		}

		template<class T>
		MemoryPool<T>::Entry::Entry():
			usecount(0),
			nextFree(-1) { }

		template<class T>
		MemoryPool<T>::Entry::Entry(MemoryPool<T>::Entry &&move):
			usecount(move.usecount),
			nextFree(move.nextFree)
		{
			if(move.usecount)
			// if object was allocated, move it.
				( new (&object) T(std::move(*&move.object)) );
		}

		template<class T>
		REINL void MemoryPool<T>::inc_ref(size_t byte_offset_entry)
		{
			RE_DBG_ASSERT(offset % type_size >= offsetof(Entry, object));
			RE_DBG_ASSERT(byte_offset < data.size()*type_size);
			RE_DBG_ASSERT(ENTRYAT(offset).usecount != 0);

			reinterpret_cast<Entry*>(reinterpret_cast<byte*>(data.data())+byte_offset_entry)->usecount++;
		}

		template<class T>
		REINL void MemoryPool<T>::dec_ref(size_t byte_offset_entry)
		{
			RE_DBG_ASSERT(byte_offset < data.size()*type_size);
			RE_DBG_ASSERT(ENTRYAT(offset).usecount != 0);

			if(!--reinterpret_cast<Entry*>(reinterpret_cast<byte*>(data.data())+byte_offset_entry)->usecount)
				free(byte_offset_entry);
		}


		template<class T>
		MemoryPool<T>::MemoryPool():
			last_allocated_object_after(0),
			data(0),
			firstFree(-1),
			entry_size(sizeof(Entry)),
			destructor(&destruct) {}
		
		template<class T>
		MemoryPool<T>::MemoryPool(size_t capacity):
			last_allocated_object_after(0)
			data(0),
			firstFree(-1),
			entry_size(sizeof(Entry)),
			destructor(&destruct)
		{
			reservePool(capacity);
		}
	}
}