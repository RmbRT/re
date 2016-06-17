#ifndef __re_intersection_hpp_defined
#define __re_intersection_hpp_defined

#include "Plane.hpp"
#include "Ray.hpp"
#include <cfloat>

namespace re
{
	namespace math
	{
		template<class T>
		/*Computes the intersection of a Ray and a Plane, as well as different representations for the intersection.
		@param[in] ray: the Ray to collide with the Plane.
		@param[in] plane: the Plane to collide with the Ray.
		@param[out] u: the coordinate on the first axis of the Plane, relative to the length of the axis vector.
		@param[out] v: the coordinate on the second axis of the Plane, relative to the length of the axis vector.
		@param[out] dist: the coordinate on the ray, relative to the direction vector of the ray.
		@note: If you pass null, then the value for that argument will not be calculated.*/
		bool intersect(const Ray<T> &ray, const STPlane<T> &plane, float *u, float *v, float *dist)
		{

			// Compute the determinant.
			vec3<T> directionCrossEdge2 = cross(ray.direction, plane.t);

			float determinant = dot(plane.s, directionCrossEdge2);

			// If the ray is parallel to the triangle plane, there is no collision.
			if (determinant > -FLT_EPSILON && determinant < FLT_EPSILON)
				return false;

			float inverseDeterminant = 1.0f / determinant;

			// Calculate the U parameter of the intersection point.
			vec3<T> distanceVector = ray.position - plane.position;
			if(u)
				*u = dot(distanceVector, directionCrossEdge2) * inverseDeterminant;

			// Calculate the V parameter of the intersection point.
			vec3<T> distanceCrossEdge1 = cross(distanceVector, plane.s);
			if(v)
				*v = dot(ray.direction, distanceCrossEdge1) * inverseDeterminant;


			// Compute the distance along the ray to the triangle.
			if(dist)
				*dist = dot(plane.t, distanceCrossEdge1) * inverseDeterminant;

			return true;
		}
	}
}

#endif