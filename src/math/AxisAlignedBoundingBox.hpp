#ifndef __re_axisalignedboundingbox_hpp_defined
#define __re_axisalignedboundingbox_hpp_defined

#include "Vector.hpp"
#include "Matrix.hpp"
#include "MathUtil.hpp"
#include "empty.hpp"

#include "../defines.hpp"
#include "../types.hpp"

namespace re
{
	namespace math
	{
		/*The precision of the AxisAlignedBoundingBox.*/
		template<class T>
		/*Represents an AxisAligned BoundingBox.*/
		class AxisAlignedBoundingBox
		{
			bool _empty;
			vec3<T> _min, _max;
		public:

			/*Constructs a BoundingBox containing only @<point>.*/
			AxisAlignedBoundingBox(const vec3<T> &point);
			/*Constructs a BoundingBox with the @<min> and @<max> values.*/
			AxisAlignedBoundingBox(const vec3<T> &min, const vec3<T> &max);
			/*Constructs an empy BoundingBox.*/
			AxisAlignedBoundingBox(empty_t);


			/*Returns whether @<position> is contained within this BoundingBox.*/
			bool contains(const vec3<T> &position) const;

			/*Returns a BoundingBox containing all points that are contained in @<this> AND in @<other>.
			If there are no such points, an empty BoundingBox is returned.*/
			AxisAlignedBoundingBox<T> operator&(const AxisAlignedBoundingBox<T> &other) const;
			/*Shrinks the BoundingBox to contain all the points that are contained in @<this> AND in @<other>.
			If there are no such points, @<this> becomes empty.*/
			AxisAlignedBoundingBox<T> &operator&=(const AxisAlignedBoundingBox<T> &other);

			/*Returns a BoundingBox containing all the points that are contained in @<this> OR in @<other>.
			Note that the resulting BoundingBox may contain additional points in order to satisfy this condition.*/
			AxisAlignedBoundingBox<T> operator|(const AxisAlignedBoundingBox<T> &other) const;
			/*Expands the BoundingBox so that it contains @<other>. If it already did contain @<other>, does nothing.*/
			AxisAlignedBoundingBox<T> &operator|=(const AxisAlignedBoundingBox<T> &other);
			/*Returns a BoundingBox containing all points contained by @<this> AND @<point>.*/
			AxisAlignedBoundingBox<T> operator|(const vec3<T> &point) const;
			/*Expands the BoundingBox so that it contains @<point>. If it already did contain @<point>, does nothing.*/
			AxisAlignedBoundingBox<T> &operator|=(const vec3<T> &point);

			/*Returns whether the BoundingBox is empty.*/
			bool empty() const;
			/*Returns the min value of the BoundingBox.*/
			const vec3<T> &min() const;
			/*Returns the max value of the boundingBox.*/
			const vec3<T> &max() const;

			/*Returns the x difference between the min and max point of @<this>.
			If @<this> is empty, returns a negative value.*/
			T sizeX() const;
			/*Returns the y difference between the min and max point of @<this>.
			If @<this> is empty, returns a negative value.*/
			T sizeY() const;
			/*Returns the z difference between the min and max point of @<this>.
			If @<this> is empty, returns a negative value.*/
			T sizeZ() const;
			/*Returns the difference between the min and max point of @<this>.
			If @<this> is empty, returns a negative value.*/
			vec3<T> size() const;
			
			/*Extends the BoundingBox to contain @<position>.*/
			void makeContain(const vec3<T> &position);
			/*Sets the BoundingBox to only contain @<point>.*/
			void setToPoint(const vec3<T> &point);
			/*Sets the BoundingBox to only contain a box defined by the @<min> and @<max> bounds.*/
			void setToBox(const vec3<T> &min, const vec3<T> &max);
			/*Sets the BoundingBox to be empty.*/
			void setToEmpty();
		};

		typedef AxisAlignedBoundingBox<int> iAABB;
		typedef AxisAlignedBoundingBox<float> fAABB;
		typedef AxisAlignedBoundingBox<double> dAABB;

	}
}


namespace re
{
	namespace math
	{
		template<class T>
		AxisAlignedBoundingBox<T>::AxisAlignedBoundingBox(const vec3<T> &point) : _min(point), _max(point), _empty(false) { }
		template<class T>
		AxisAlignedBoundingBox<T>::AxisAlignedBoundingBox(const vec3<T> &min, const vec3<T> &max): _min(min), _max(max), _empty(_min.x>_max.x || _min.y>_max.y || _min.z>_max.z) { }
		template<class T>
		AxisAlignedBoundingBox<T>::AxisAlignedBoundingBox(empty_t): _min(), _max(), _empty(true) { }

		template<class T>
		bool AxisAlignedBoundingBox<T>::contains(const vec3<T> &position) const
		{
			return (!_empty)
				&& (_min.x<=position.x && position.x<=_max.x)
				&& (_min.y<=position.y && position.y<=_max.y)
				&& (_min.z<=position.z && position.z<=_max.z);
		}
		template<class T>
		AxisAlignedBoundingBox<T> AxisAlignedBoundingBox<T>::operator&(const AxisAlignedBoundingBox<T> &other) const
		{
			if(_empty)
			{
				if(other._empty)
					return AxisAlignedBoundingBox<T>(math::empty);
				else
					return other;
			}
			else
			{
				if(other._empty)
					return *this;
				else
				{
					return AxisAlignedBoundingBox<T>(
						vec3<T>(
							math::max(_min.x, other._min.x),
							math::max(_min.y, other._min.y),
							math::max(_min.z, other._min.z)),
						vec3<T>(
							math::min(_max.x, other._max.x),
							math::min(_max.y, other._max.y),
							math::min(_max.z, other._max.z)));
				}
			}
		}

		template<class T>
		AxisAlignedBoundingBox<T> &AxisAlignedBoundingBox<T>::operator&=(const AxisAlignedBoundingBox<T> &other)
		{
			if(_empty)
				return *this;
			if(other._empty)
				return *this=other;
			
			_min.x = math::max(_min.x, other._min.x);
			_min.y = math::max(_min.y, other._min.y);
			_min.z = math::max(_min.z, other._min.z);

			_max.x = math::min(_max.x, other._max.x);
			_max.y = math::min(_max.y, other._max.y);
			_max.z = math::min(_max.z, other._max.z);

			return *this;
		}

		template<class T>
		AxisAlignedBoundingBox<T> AxisAlignedBoundingBox<T>::operator|(const AxisAlignedBoundingBox<T> &other) const
		{
			if(_empty)
				return other;
			if(other._empty)
				return *this;

			return AxisAlignedBoundingBox<T>(
				vec3<T>(
					math::min(_min.x, other._min.x),
					math::min(_min.y, other._min.y),
					math::min(_min.z, other._min.z)),
				vec3<T>(
					math::max(_max.x, other._max.x),
					math::max(_max.y, other._max.y),
					math::max(_max.z, other._max.z)));
		}
		template<class T>
		AxisAlignedBoundingBox<T> &AxisAlignedBoundingBox<T>::operator|=(const AxisAlignedBoundingBox<T> &other)
		{
			if(_empty)
				return *this=other;
			if(_other._empty)
				return *this;
			
			_min.x = math::min(_min.x, other._min.x);
			_min.y = math::min(_min.y, other._min.y);
			_min.z = math::min(_min.z, other._min.z);

			_max.x = math::max(_max.x, other._max.x);
			_max.y = math::max(_max.y, other._max.y);
			_max.z = math::max(_max.z, other._max.z);
			
			return *this;
		}
		template<class T>
		AxisAlignedBoundingBox<T> AxisAlignedBoundingBox<T>::operator|(const vec3<T> &point) const
		{
			if(_empty)
				return AxisAlignedBoundingBox<T>(point);
			else
				return AxisAlignedBoundingBox<T>(
					vec3<T>(
						math::min(_min.x, point.x),
						math::min(_min.y, point.y),
						math::min(_min.z, point.z)),
					vec3<T>(
						math::max(_max.x, point.x),
						math::max(_max.y, point.y),
						math::max(_max.z, point.z)));
		}
		template<class T>
		AxisAlignedBoundingBox<T> &AxisAlignedBoundingBox<T>::operator|=(const vec3<T> &point)
		{
			if(_empty)
				return *this=point;
			
			_min.x = math::min(_min.x, point.x);
			_min.y = math::min(_min.y, point.y);
			_min.z = math::min(_min.z, point.z);

			_max.x = math::max(_max.x, point.x);
			_max.y = math::max(_max.y, point.y);
			_max.z = math::max(_max.z, point.z);

			return *this;
		}
		template<class T>
		bool AxisAlignedBoundingBox<T>::empty() const
		{
			return _empty;
		}
		template<class T>
		const vec3<T> &AxisAlignedBoundingBox<T>::min() const
		{
			return _min;
		}
		template<class T>
		const vec3<T> &AxisAlignedBoundingBox<T>::max() const
		{
			return _max;
		}
		template<class T>
		T AxisAlignedBoundingBox<T>::sizeX() const
		{
			return _empty?T(-1):_max.x-_min.x;
		}
		template<class T>
		T AxisAlignedBoundingBox<T>::sizeY() const
		{
			return _empty?T(-1):_max.y-_min.y;
		}
		template<class T>
		T AxisAlignedBoundingBox<T>::sizeZ() const
		{
			return _empty?T(-1):_max.z-_min.z;
		}

		template<class T>
		vec3<T> AxisAlignedBoundingBox<T>::size() const
		{
			return _empty?vec3<T>(T(-1),T(-1),T(-1)):_max-_min;
		}

		template<class T>
		void AxisAlignedBoundingBox<T>::makeContain(const vec3<T> &position)
		{
			operator|=(position);
		}
		template<class T>
		void AxisAlignedBoundingBox<T>::setToPoint(const vec3<T> &position)
		{
			operator=(position);
		}
		template<class T>
		void AxisAlignedBoundingBox<T>::setToBox(const vec3<T> &min, const vec3<T> &max)
		{
			operator=(AxisAlignedBoundingBox<T>(min,max));
		}
		template<class T>
		void AxisAlignedBoundingBox<T>::setToEmpty()
		{
			operator=(math::empty);
		}
	}
}

#endif