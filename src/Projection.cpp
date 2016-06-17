#include "Projection.hpp"

namespace re
{

	Projection::Projection(const math::Angle &fov, const math::fvec2 &size, float near_plane, float far_plane)
		: type(ProjectionType::Perspective), fov(fov), position(), size(size), near_plane(near_plane), far_plane(far_plane) { }
	Projection::Projection(const math::fvec2 &pos, const math::fvec2 &size, float near_plane, float far_plane)
		: type(ProjectionType::Orthogonal), fov(), position(pos), size(size), near_plane(near_plane), far_plane(far_plane) { }

	math::fmat4x4 Projection::projectionMatrix() const
	{
		if(type == ProjectionType::Orthogonal)
			return math::fmat4x4::ortho(position.x, position.y, position.x+size.x, position.y+size.y, near_plane, far_plane);
		else
			return math::fmat4x4::perspective(fov, size.x, size.y, near_plane, far_plane);
	}

	math::Ray<float> Projection::unproject(const math::fvec2 &position) const
	{
		// delta position from the middle of the view, in view space
		// range is (-1 .. 1, -1 .. 1)
		const math::fvec2 d(position.x*2/size.x, -position.y*2/size.y);

		if(type == ProjectionType::Orthogonal)
			return math::Ray<float>(math::fvec3(d.x*size.x/2+this->position.x, d.y*size.y/2+this->position.y, 0), math::fvec3(0,0,1));
		else
		{
			const float tan_fov_2 = tanf(fov.rad() / 2);
			const float aspect = size.x/size.y;
			const float t_y = tan_fov_2 * d.y;
			const float t_x = tan_fov_2 * d.x * aspect;

			math::fvec3 dir(t_x, t_y, 1);

			return math::Ray<float>(math::fvec3(0,0,0), dir);
		}
	}

	math::Ray<float> Projection::unproject(const math::fvec2 &position, const math::fmat4x4 &inv_view) const
	{
		// delta position from the middle of the view, in view space
		// range is (-1 .. 1, -1 .. 1)
		const math::fvec2 d(position.x*2/size.x-1, 1.f-position.y*2/size.y);

		if(type == ProjectionType::Orthogonal)
			return math::Ray<float>(math::fvec3(d.x*size.x/2+this->position.x, d.y*size.y/2+this->position.y, 0), math::fvec3(0,0,1));
		else
		{
			const float tan_fov_2 = tanf(fov.rad() / 2);
			const float aspect = size.x/size.y;
			const float t_y = tan_fov_2 * d.y;
			const float t_x = tan_fov_2 * d.x * aspect;

			math::fvec3 dir(t_x, t_y, 1);
			math::fvec3 origin(0,0,0);
			origin = math::fvec3(inv_view * math::fvec4(origin,1));
			dir = math::fvec3(inv_view * math::fvec4(dir,1)) - origin;

			return math::Ray<float>(origin, dir);
		}
	}



	math::fvec2 Projection::project(const math::fvec3 &position) const
	{
		return math::fvec2(projectionMatrix() * math::fvec4(position, 1.f));
	}

	std::vector<math::fvec2> Projection::project(const std::vector<math::fvec3> &position) const
	{
		std::vector<math::fvec2> out;
		out.reserve(position.size());

		const math::fmat4x4 &proj = projectionMatrix();

		for(size_t i = out.size()-1; i-->0;)
			out.push_back(math::fvec2(proj * math::fvec4(position[i],1)));
		return out;
	}
}