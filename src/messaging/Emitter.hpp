#ifndef __re_emitter_hpp_defined
#define __re_emitter_hpp_defined

#include <vector>

namespace re
{
	namespace messaging
	{
		template<class T>
		class Emitter;

		template<class T>
		class Receiver
		{	friend class Emitter<T>;
			std::vector<Emitter<T>*> emitters;
		public:
			virtual void onReceive(const T &obj) {}
			/*Creates a Receiver object that does not listen to anything yet.*/
			Receiver();
			/*Creates a Receiver object and registers it to the given Emitter.*/
			explicit Receiver(Emitter<T> &emitter);
			/*Unlistens from all currently listened Emitters.*/
			~Receiver();

			void listen(Emitter<T> &emitter);
			void unlisten(Emitter<T> &emitter);
		};
		
		template<class T>
		/*A class for broadcasting objects to registered callback receivers.
		Callbacks registered via @[re::messaging::Emitter<T>::registerListener] are called upon invoking @[re::messaging::Emitter<T>::emit].
		@param[class] T
			The type of the object that is to be passed on via @[re::messaging::Emitter<T>::emit].
			Note that a const reference type will be passed on.*/
		class Emitter
		{	friend class Receiver<T>;
			/*The list of all receivers that are currently registered.*/
			std::vector<Receiver<T>*> recvs;
		public:
			/*Destroys the Emitter and removes all listening Receivers*/
			~Emitter();
			/*Broadcasts the given argument to all registered callbacks
			@param[in] obj
				The object to be broadcasted.*/
			void emit(const T &obj);
		};

	}
}


namespace re
{
	namespace messaging
	{
		template<class T>
		Receiver<T>::Receiver(): emitters()	{	}
		template<class T>
		Receiver<T>::Receiver(Emitter<T> &emitter): emitters()	{	listen(emitter);	}
		template<class T>
		Receiver<T>::~Receiver()
		{
			for(auto emitter : emitters)
				unlisten(*emitter);
			emitters.clear();
		}
		
		template<class T>
		void Receiver<T>::listen(Emitter<T> &emitter)
		{
			emitter.recvs.push_back(this);
			emitters.push_back(&emitter);
		}
		
		template<class T>
		void Receiver<T>::unlisten(Emitter<T> &emitter)
		{
			for(auto it = emitter.recvs.begin(); it != emitter.recvs.end(); it++)
			{
				if((*it) == this)
				{
					emitter.recvs.erase(it);
					return;
				}
			}
		}
		template<class T>
		void Emitter<T>::emit(const T &obj)
		{
			for(auto fn : recvs)
				fn->onReceive(obj);
		}
		template<class T>
		Emitter<T>::~Emitter()
		{
			
			for(auto recv : recvs)
			{
				if(recv->emitters.empty())
					continue;


				if(!recv->emitters.empty())
					for(std::vector<Emitter<T>*>::iterator it = recv->emitters.begin(); it != recv->emitters.end(); it++)
						if(*it == this)
						{
							recv->emitters.erase(it);
							break;
						}
			}
			recvs.clear();
		}
	}
}
#endif