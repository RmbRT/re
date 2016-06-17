#ifndef __re_projection_hpp_defined
#define __re_projection_hpp_defined

#include "math/Matrix.hpp"
#include "math/Angle.hpp"
#include "math/Ray.hpp"

#include <vector>

namespace re
{
	/*The mode of a projection.*/
	RE_ENUM (ProjectionType)
	{
		Orthogonal,
		Perspective
	};

	/*A Projection that can either be a perspective or orthogonal Projection.*/
	class Projection
	{
		ProjectionType type;
		math::Angle fov;
		math::fvec2 position;
		math::fvec2 size;
		float near_plane;
		float far_plane;
	public:
		/*Creates a perspective Projection.
		@param[in] fov: the field of view of the Projection.
		@param[in] size: used to calculate the aspect ratio.
		@param[in] near_plane: the near clip plane.
		@param[in] far_plane: the far clip plane.*/
		Projection(const math::Angle &fov, const math::fvec2 &size, float near_plane, float far_plane);

		/*Creates an Orthogonal Projection.
		@param[in] pos: the coordinates that will be projected into the origin.
		@param[in] size: the width and height of the projection
		@param[in] near_plane: the near clip plane.
		@param[in] far_plane: the far clip plane.*/
		Projection(const math::fvec2 &pos, const math::fvec2 &size, float near_plane, float far_plane);
		
		/*Calculates the projection Matrix.
		@note: this can be expensive, so avoid redundant calls.*/
		math::fmat4x4 projectionMatrix() const;

		/*Creates a ray for ray casting.
		@param[in] position: the local position of the ray (i.e. cursor position).*/
		math::Ray<float> unproject(const math::fvec2 &position) const;

		/*Creates a ray for ray casting.
		@param[in] position: the local position of the ray (i.e. cursor position).
		@param[in] inv_view: the inverse view / camera matrix.
		@note: not tested yet.*/
		math::Ray<float> unproject(const math::fvec2 &position, const math::fmat4x4 &inv_view) const;
		/*Projects an input vector into projected space.
		@note:
			this calculates the projection matrix, so it uses redundant calculation!
			To avoid this overhead, call project with a collection of input vectors.*/
		math::fvec2 project(const math::fvec3 &position) const;

		/*Projects a collection of input vectors into projected space.*/
		std::vector<math::fvec2> project(const std::vector<math::fvec3> &position) const;
	};
}

#endif