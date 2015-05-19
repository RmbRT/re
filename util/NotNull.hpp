#ifndef __re_util_notnull_hpp_defined
#define __re_util_notnull_hpp_defined

#include "../defines.hpp"

namespace re
{
	namespace util
	{
		template<class T>
		struct notnull;

		template<class T>
		struct unsafe;

		template<class U, class T>
		/*Performs a dynamic cast on the given notnull. Because dynamic_cast may return null, this returns an unsafe.*/
		unsafe<U> REPTRCAST dynamic(const notnull<T> &value) { return dynamic_cast<U*>(value.data); }
		template<class U, class T>
		/*Performs a static cast on the given notnull.*/
		notnull<U> REPTRCAST cast(const notnull<T> &value) { return *static_cast<U*>(value.data); }
		template<class U, class T>
		/*Performs a reinterpret cast on the given notnull.*/
		notnull<U> REPTRCAST reinterpret(const notnull<T> &value) { return *reinterpret_cast<U*>(value.data); }

		
		template<class U, class T>
		unsafe<U> REPTRCAST dynamic(const unsafe<T> &value) { return dynamic_cast<U*>(value.data); }
		template<class U, class T>
		unsafe<U> REPTRCAST cast(const unsafe<T> &value) { return static_cast<U*>(value.data); }
		template<class U, class T>
		unsafe<U> REPTRCAST reinterpret(const unsafe<T> &value) { return reinterpret_cast<U*>(value.data); }

		template<class U, class T>
		/*Performs a dynamic cast on the given object and creates an unsafe.*/
		unsafe<U> REPTRCAST dynamic(T &value) { return dynamic_cast<U*>(reinterpret_cast<T*>(const_cast<char*>(&reinterpret_cast<const char&>((value))))); }
		template<class U, class T>
		notnull<U> REPTRCAST cast(T &value) { return static_cast<U&>(value); }
		template<class U, class T>
		notnull<U> REPTRCAST reinterpret(T &value) { return reinterpret_cast<U&>(value); }

		template<class U, class T>
		/*Performs a dynamic cast on the given object and creates an unsafe.*/
		unsafe<U> REPTRCAST dynamic(T *value) { return dynamic_cast<U*>(reinterpret_cast<T*>(const_cast<char*>(&reinterpret_cast<const char&>((value))))); }
		template<class U, class T>
		unsafe<U> REPTRCAST cast(T *value) { return static_cast<U*>(value); }
		template<class U, class T>
		unsafe<U> REPTRCAST reinterpret(T *value) { return reinterpret_cast<U*>(value); }


		template<class U, class T>
		unsafe<U> REPTRCAST cast(unsafe<T> &value) { return cast<U>(value.data); }

		template<class U, class T>
		notnull<U> REPTRCAST cast(notnull<T> &value) { return cast<U>(value.data); }

		template<class T>
		/*Stores a pointer to an object, which may or may not be null.
		Note that this does not affect the lifetime of the referenced object in any way,
		as it is treated like a raw reference or pointer. Note that, to access the element pointed to by unsafe,
		you have to use the pointer syntax.*/
		struct unsafe
		{
			T* data;

		public:
			unsafe(T* data): data(data) { }
			unsafe(const notnull<T> &rhs): data((T*)rhs) { }
			unsafe(T& data): data(reinterpret_cast<T*>(const_cast<char*>(&reinterpret_cast<const char&>(data)))) { }
			unsafe(std::nullptr_t): data(nullptr) { }
			unsafe(): data(nullptr) { }
			template<class U>
			unsafe(const unsafe<U> &other): unsafe(cast<T>(other)) { }
			template<class U>
			unsafe(U* data): unsafe(cast<T>(data)) { }
			template<class U>
			unsafe(U &data): unsafe(cast<T>(data)) { }
			
			operator bool() const { return data != nullptr; }
			T& operator*() const { return *data; }
			notnull<T> operator->() const { return *data; }
			operator notnull<T>() const { return *data; }
			
			bool __fastcall operator!=(const T* other) const { return data != other; }
			bool __fastcall operator!=(const T& other) const { return data != reinterpret_cast<const T*>(&reinterpret_cast<const char &>(other)); }
			bool __fastcall operator!=(const unsafe<const T> &other) const { return data != other.data; }
			bool __fastcall operator!=(const notnull<const T> &other) const { return data != other.data; }

			bool __fastcall operator==(const notnull<const T> &other) const { return data == other.data; }
			bool __fastcall operator==(const unsafe<const T> &other) const { return data == other.data; }
			bool __fastcall operator==(const T* other) const { return data == other; }
		};

		template<class T>
		/*Stores a pointer to an object, which is guaranteed not to be null.
		Note that this does not affect the lifetime of the referenced object in any way,
		as it is treated like a normal reference or pointer. Note that, to access the element pointed to by notnull,
		you have to use the pointer syntax (->).*/
		struct notnull
		{
			template<class U> friend unsafe<U> REPTRCAST dynamic(const notnull<T> &value);
			template<class U> friend notnull<U> REPTRCAST cast(const notnull<T> &value);
			template<class U> friend notnull<U> REPTRCAST reinterpret(const notnull<T> &value);
		
			template<class U> friend unsafe<U> REPTRCAST dynamic(const unsafe<T> &value);
			template<class U> friend unsafe<U> REPTRCAST cast(const unsafe<T> &value);
			template<class U> friend unsafe<U> REPTRCAST reinterpret(const unsafe<T> &value);

			template<class U> friend unsafe<U> REPTRCAST dynamic(T &value);
			template<class U> friend notnull<U> REPTRCAST cast(T &value);
			template<class U> friend notnull<U> REPTRCAST reinterpret(T &value);
			T* data;
		public:
			notnull(T &data): data(reinterpret_cast<T*>(const_cast<char*>(&reinterpret_cast<const char&>(data)))) {}
			notnull(const notnull<T> &other): data(other.data) { }
			notnull(notnull<T> &&move) : data(move.data) { }
			template<class U>
			notnull(const notnull<U> &other): notnull(cast<T>(other)) { }
			template<class U>
			notnull(U &data): notnull(cast<T>(data)) { }

			T& operator*() const { return *data; }
			T* operator->() const { return data; }
			operator T&() const { return *data; }
			operator T*() const { return data; }

			bool __fastcall operator!=(const T* other) const { return data != other; }
			bool __fastcall operator!=(const T& other) const { return data != reinterpret_cast<const T*>(&reinterpret_cast<const char &>(other)); }
			bool __fastcall operator!=(const unsafe<const T> &other) const { return data != other.data; }

			bool __fastcall operator==(const T* other) const { return data == other; }
			bool __fastcall operator==(const unsafe<const T> &other) const { return data == other.data; }
			//bool __fastcall operator==(const notnull<const T> &other) const { return data == other.data; }
			bool __fastcall operator==(const notnull<T> &other) const { return data == other.data; }
		};
	}
}

#endif