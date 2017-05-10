#include "Projection.hpp"

namespace re
{

	Projection::Projection(
		math::Angle const& fov,
		math::fvec2_t const& size,
		float near_plane,
		float far_plane):
		type(ProjectionType::Perspective),
		fov(fov),
		position(),
		size(size),
		near_plane(near_plane),
		far_plane(far_plane)
	{
	}

	Projection::Projection(
		math::fvec2_t const& pos,
		math::fvec2_t const& size,
		float near_plane,
		float far_plane):
		type(ProjectionType::Orthogonal),
		fov(),
		position(pos),
		size(size),
		near_plane(near_plane),
		far_plane(far_plane)
	{
	}

	math::fmat4x4_t Projection::projectionMatrix() const
	{
		if(type == ProjectionType::Orthogonal)
			return math::fmat4x4_t::ortho(position.x, position.y, position.x+size.x, position.y+size.y, near_plane, far_plane);
		else
			return math::fmat4x4_t::perspective(fov, size.x, size.y, near_plane, far_plane);
	}

	math::Ray<float> Projection::unproject(math::fvec2_t const& position) const
	{
		// delta position from the middle of the view, in view space
		// range is (-1 .. 1, -1 .. 1)
		const math::fvec2_t d(position.x*2/size.x, -position.y*2/size.y);

		if(type == ProjectionType::Orthogonal)
			return math::Ray<float>(math::fvec3_t(d.x*size.x/2+this->position.x, d.y*size.y/2+this->position.y, 0), math::fvec3_t(0,0,1));
		else
		{
			const float tan_fov_2 = tanf(fov.rad() / 2);
			const float aspect = size.x/size.y;
			const float t_y = tan_fov_2 * d.y;
			const float t_x = tan_fov_2 * d.x * aspect;

			math::fvec3_t dir(t_x, t_y, 1);

			return math::Ray<float>(math::fvec3_t(0,0,0), dir);
		}
	}

	math::Ray<float> Projection::unproject(math::fvec2_t const& position, math::fmat4x4_t const& inv_view) const
	{
		// delta position from the middle of the view, in view space
		// range is (-1 .. 1, -1 .. 1)
		const math::fvec2_t d(position.x*2/size.x-1, 1.f-position.y*2/size.y);

		if(type == ProjectionType::Orthogonal)
			return math::Ray<float>(math::fvec3_t(d.x*size.x/2+this->position.x, d.y*size.y/2+this->position.y, 0), math::fvec3_t(0,0,1));
		else
		{
			const float tan_fov_2 = tanf(fov.rad() / 2);
			const float aspect = size.x/size.y;
			const float t_y = tan_fov_2 * d.y;
			const float t_x = tan_fov_2 * d.x * aspect;

			math::fvec3_t dir(t_x, t_y, 1);
			math::fvec3_t origin(0,0,0);
			origin = math::fvec3_t(inv_view * math::fvec4_t(origin,1));
			dir = math::fvec3_t(inv_view * math::fvec4_t(dir,1)) - origin;

			return math::Ray<float>(origin, dir);
		}
	}



	math::fvec2_t Projection::project(math::fvec3_t const& position) const
	{
		return math::fvec2_t(projectionMatrix() * math::fvec4_t(position, 1.f));
	}

	std::vector<math::fvec2_t> Projection::project(
		std::vector<math::fvec3_t> const& position) const
	{
		std::vector<math::fvec2_t> out;
		out.reserve(position.size());

		math::fmat4x4_t const& proj = projectionMatrix();

		for(size_t i = out.size()-1; i-->0;)
			out.push_back(math::fvec2_t(proj * math::fvec4_t(position[i],1)));
		return out;
	}
}