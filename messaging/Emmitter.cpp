#include "Emmitter.hpp"

namespace re
{
	namespace messaging
	{
		template<class T>
		void Emmitter<T>::emmit(const T &obj)
		{
			for(auto fn : recvs)
				fn(obj);
		}
		
		template<class T>
		void Emmitter<T>::registerListener(Emmitter<T>::RecvFn recvFn)
		{
			recvs.push_back(recvFn);
		}
		
		template<class T>
		void Emmitter<T>::unregisterListener(Emmitter<T>::RecvFn recvFn)
		{
			for(auto it = recvs.cbegin(); it != recvs.cend(); it++)
			{
				if((*it) == recvFn)
					recvs.erase(it);
			}
		}
		
		
		template<class T, class U>
		void Emmitter<T, U>::emmit(const T &obj, const U &obj2)
		{
			for(auto fn : recvs)
				fn(obj, obj2);
		}
		
		template<class T, class U>
		void Emmitter<T, U>::registerListener(Emmitter<T, U>::RecvFn recvFn)
		{
			recvs.push_back(recvFn);
		}
		
		template<class T, class U>
		void Emmitter<T, U>::unregisterListener(Emmitter<T, U>::RecvFn recvFn)
		{
			for(auto it = recvs.cbegin(); it != recvs.cend(); it++)
			{
				if((*it) == recvFn)
					recvs.erase(it);
			}
		}
		
		
		
		template<class T, class U, class V>
		void Emmitter<T, U, V>::emmit(const T &obj, const U &obj2, const V &obj3)
		{
			for(auto fn : recvs)
				fn(obj, obj2, obj3);
		}
		
		template<class T, class U, class V>
		void Emmitter<T, U, V>::registerListener(Emmitter<T, U, V>::RecvFn recvFn)
		{
			recvs.push_back(recvFn);
		}
		
		template<class T, class U, class V>
		void Emmitter<T, U, V>::unregisterListener(Emmitter<T, U, V>::RecvFn recvFn)
		{
			for(auto it = recvs.cbegin(); it != recvs.cend(); it++)
			{
				if((*it) == recvFn)
					recvs.erase(it);
			}
		}
		
		
	}
}