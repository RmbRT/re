namespace re
{
	namespace util
	{
		template<class T>
		std::vector<T> detail::AllocationBufferStorage<T>::buffer;

		template<class T>
		T * allocation_buffer(size_t count)
		{
			if(detail::AllocationBufferStorage<T>::buffer.size() < count)
				detail::AllocationBufferStorage<T>::buffer.resize(count);

			return detail::AllocationBufferStorage<T>::buffer.data();
		}

		template<class T>
		void free_allocation_buffer()
		{
			detail::AllocationBufferStorage<T>::buffer.clear();
		}
	}
}