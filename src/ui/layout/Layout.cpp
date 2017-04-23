#include "Layout.hpp"

namespace re
{
	namespace ui
	{
		namespace layout
		{

			static float get_texcoord(
				float vertex,
				size_t tex_size,
				Repeat repeat,
				float scale)
			{
				switch(repeat)
				{
				case Repeat::Tile:
					{
						return vertex / tex_size / scale;
					} break;
				case Repeat::Fit:
					{
						return 1;
					} break;
				default:
					{
						RE_ASSERTION_FAILURE("invalid enum constant");
					} break;
				}
			}

			Image::Image(
				graphics::gl::BufferAccess access):
				m_repeat(Repeat::Fit, Repeat::Fit),
				m_texture_scale(1,1),
				m_color(1,1,1,1),
				m_texture(nullptr),
				m_position(0,0),
				m_size(0,0),
				m_model(access, BufferUsage::Draw),
				m_invalid_model(true)
			{
			}

			void Image::set_repeat(
				math::Vec2<Repeat> const& repeat)
			{
				if(m_repeat != repeat)
				{
					m_invalid_model = true;
					m_repeat = repeat;
				}
			}

			void Image::set_repeat(
				Repeat repeat)
			{
				set_repeat({repeat, repeat});
			}

			void Image::set_image(
				math::fvec4_t const& color)
			{
				set_image(nullptr, color);
			}
			void Image::set_image(
				Shared<graphics::gl::Texture2D> texture)
			{
				set_image(texture, {1,1,1,1});
			}

			void Image::set_image(
				Shared<graphics::gl::Texture2D> texture,
				math::fvec4_t const& color)
			{
				if(m_color != color)
					m_invalid_model = true;
				m_texture = std::move(texture);
				m_color = color;
			}

			void Image::set_position(
				math::fvec3_t const& position)
			{
				if(m_position != position)
				{
					m_invalid_model = true;
					m_position = position;
				}
			}

			void Image::set_size(
				math::fvec2_t const& size)
			{
				if(m_size != size)
				{
					m_invalid_model = true;
					m_size = size;
				}
			}

			void Image::set_texture_scale(
				math::fvec2_t const& scale)
			{
				RE_DBG_ASSERT(scale.x != 0);
				RE_DBG_ASSERT(scale.y != 0);

				if(m_texture_scale != scale)
				{
					m_invalid_model = true;
					m_texture_scale = scale;
				}
			}

			void Image::update_model() const
			{
				if(!m_invalid_model)
					return;
				m_invalid_model = false;

				math::fvec3_t end = m_position + math::fvec3_t(m_size.x, m_size.y, 0);
				math::fvec2_t tex_origin = { 0, 0 };

				math::fvec2_t tex_end;
				if(m_texture)
					tex_end = {
					get_texcoord(
						m_size.x,
						m_texture->width(),
						m_repeat.x,
						m_texture_scale.x),
					get_texcoord(
						m_size.y,
						m_texture->height(),
						m_repeat.y,
						m_texture_scale.y)
				};

				std::vector<Vertex> vertices = {
					Vertex(m_position, tex_origin, m_color),
					Vertex({m_position.x, end.y, m_position.z}, {tex_origin.x, tex_end.y}, m_color),
					Vertex({end.x, m_position.y, m_position.z}, {tex_end.x, tex_origin.y}, m_color),
					Vertex(end, tex_end, m_color)
				};
				std::vector<graphics::gl::index_t> indices = {
					0, 1, 2,
					2, 1, 3
				};

				if(!m_model.exists())
					m_model.alloc();

				m_model.set_data(
					std::move(vertices),
					graphics::gl::RenderMode::Triangles,
					std::move(indices));
			}

			void Image::draw() const
			{
				update_model();

				if(m_texture)
					m_texture->bind();
				else
					Texture2D::unbind();

				m_model.draw();
			}

			void Borders::set_left_repeat(
				math::Vec2<Repeat> repeat)
			{
				m_borders.left.set_repeat(repeat);
			}
			void Borders::set_right_repeat(
				math::Vec2<Repeat> const& repeat)
			{
				m_borders.right.set_repeat(repeat);
			}
			void Borders::set_top_repeat(
				math::Vec2<Repeat> const& repeat)
			{
				m_borders.top.set_repeat(repeat);
			}
			void Borders::set_bottom_repeat(
				math::Vec2<Repeat> const& repeat)
			{
				m_borders.bottom.set_repeat(repeat);
			}
			void Borders::set_horizontal_repeat(
				math::Vec2<Repeat> const& repeat)
			{
				m_borders.top.set_repeat(repeat);
				m_borders.bottom.set_repeat(repeat);
			}
			void Borders::set_vertical_repeat(
				math::Vec2<Repeat> const& repeat)
			{
				m_borders.left.set_repeat(repeat);
				m_borders.right.set_repeat(repeat);
			}
			void Borders::set_top_left_repeat(
				math::Vec2<Repeat> const& repeat)
			{
				m_corners.top_left.set_repeat(repeat);
			}

			void Borders::set_top_right_repeat(
				math::Vec2<Repeat> const& repeat)
			{
				m_corners.top_right.set_repeat(repeat);
			}

			void Borders::set_bottom_left_repeat(
				math::Vec2<Repeat> const& repeat)
			{
				m_corners.bottom_left.set_repeat(repeat);
			}
			void Borders::set_bottom_right_repeat(
				math::Vec2<Repeat> const& repeat)

			{
				m_corners.bottom_right.set_repeat(repeat);
			}

			void Borders::set_corner_repeat(
				math::Vec2<Repeat> const& repeat)
			{
				m_corners.top_left.set_repeat(repeat);
				m_corners.top_right.set_repeat(repeat);
				m_corners.bottom_left.set_repeat(repeat);
				m_corners.bottom_right.set_repeat(repeat);
			}

			void Borders::set_left_image(
				Shared<graphics::gl::Texture2D> texture,
				math::fvec4_t const& color)
			{
				m_borders.left.set_image(std::move(texture), color);
			}
			void Borders::set_right_image(
				Shared<graphics::gl::Texture2D> texture,
				math::fvec4_t const& color)
			{
				m_borders.right.set_image(std::move(texture)), color);
			}
			void Borders::set_top_image(
				Shared<graphics::gl::Texture2D> texture,
				math::fvec4_t const& color)
			{
				m_borders.top.set_image()std::move(texture), color);
			}
			void Borders::set_bottom_image(
				Shared<graphics::gl::Texture2D> texture,
				math::fvec4_t const& color)
			{
				m_borders.bottom.set_image(std::move(texture), color);
			}

			void Borders::set_top_left_image(
				Shared<graphics::gl::Texture2D> texture,
				math::fvec4_t const& color)
			{
				m_corners.top_left.set_image(std::move(texture), color);
			}
			void Borders::set_top_right_image(
				Shared<graphics::gl::Texture2D> texture,
				math::fvec4_t const& color)
			{
				m_corners.top_right.set_image(std::move(texture), color);
			}
			void Borders::set_bottom_left_image(
				Shared<graphics::gl::Texture2D> texture,
				math::fvec4_t const& color)
			{
				m_corners.bottom_left.set_image(std::move(texture), color);
			}
			void Borders::set_bottom_right_image(
				Shared<graphics::gl::Texture2D> texture,
				math::fvec4_t const& color)
			{
				m_corners.bottom_right.set_image(std::move(textures), color);
			}

			void Borders::set_left_texture_scale(
				math::fvec2_t const& scale)
			{
				m_borders.left.set_texture_scale(scale);
			}
			void Borders::set_right_texture_scale(
				math::fvec2_t const& scale)
			{
				m_borders.right.set_texture_scale(scale);
			}
			void Borders::set_top_texture_scale(
				math::fvec2_t const& scale)
			{
				m_borders.top.set_texture_scale(scale);
			}
			void Borders::set_bottom_texture_scale(
				math::fvec2_t const& scale)
			{
				m_borders.bottom.set_texture_scale(scale);
			}
			void Borders::set_mirrored_border_texture_scale(
				math::fvec2_t const& scale)
			{
				m_borders.top.set_texture_scale(scale);
				m_borders.left.set_texture_scale(scale);
				m_borders.right.set_texture_scale({-scale.x, scale.y});
				m_borders.bottom.set_texture_scale({scale.x, -scale.y});
			}

			void Borders::set_top_left_texture_scale(
				math::fvec2_t const& scale)
			{
				m_corners.top_left.set_texture_scale(scale);
			}

			void Borders::set_top_right_texture_scale(
				math::fvec2_t const& scale)
			{
				m_scorners.top_right.set_texture_scale(scale);
			}
			void Borders::set_bottom_left_texture_scale(
				math::fvec2_t const& scale)
			{
				m_corners.bottom_left.set_texture_scale(scale);
			}
			void Borders::set_bottom_right_texture_scale(
				math::fvec2_t const& scale)
			{
				m_corners.bottom_right.set_texture_scale(scale);
			}

			void Borders::set_mirrored_corner_exture_scale(
				math::fvec2_t const& scale)
			{
				m_corners.top_left.set_texture_scale(scale);
				m_corners.top_right.set_texture_scale({-scale.x, scale.y});
				m_corners.bottom_left.set_texture_scale({scale.x, -scale.y});
				m_corners.bottom_right.set_texture_scale({-scale.x, -scale.y});
			}

			void Borders::set_box(
				math::fvec3_t const& origin,
				math::fvec2_t const& inner_size)
			{
				// borders.

				m_borders.top.set_position({
					origin.x + m_width.left,
					origin.y});
				m_borders.top.set_size({inner_size.x, m_width.top});

				m_borders.bottom.set_position({
					origin.x + m_width.left,
					origin.y + m_width.top + inner_size.y});
				m_borders.bottom.set_size({inner_size.x, m_width.bottom});

				m_borders.left.set_position({
					origin.x,
					origin.y + m_width.top});
				m_borders.right.set_size({m_width.left, inner_size.y});

				m_borders.right.set_position({
					origin.x + m_width.left + inner_size.x,
					origin.y + m_width.top});
				m_borders.right.set_size({m_width.right, inner_size.y});

				// corners.

				m_corners.top_left.set_position(origin);
				m_corners.top_left.set_size({m_width.left, m_width.top});

				m_corners.top_right.set_position({
					origin.x + m_width.left + inner_size.x,
					origin.y});
				m_corners.top_right.set_size({m_width.right, m_width.top});

				m_corners.bottom_left.set_position({
					origin.x,
					origin.y + m_width.top + inner_size.y});
				m_corners.bottom_left.set_size({
					m_width.left,
					m_width.bottom});

				m_corners.bottom_right.set_position({
					origin.x + m_width.left + inner_size.x,
					origin.y + m_width.top + inner_size.y});
				m_corners.bottom_left.set_size({
					m_width.right,
					m_width.bottom});
			}

			void Borders::update_model() const
			{
				m_borders.top.update_model();
				m_borders.bottom.update_model();
				m_borders.left.update_model();
				m_borders.right.update_model();

				m_corners.top_left.update_model();
				m_corners.top_right.update_model();
				m_corners.bottom_left.update_model();
				m_corners.bottom_right.update_model();
			}

			void Borders::draw() const
			{
				update_model();

				if(m_width.top)
				{
					if(m_width.left)
						m_corners.top_left.draw();
					m_borders.top.draw();
					if(m_width.right)
						m_corners.top_right.draw();
				}
				if(m_width.left)
					m_corners.left.draw();
				if(m_width.right)
					m_corners.right.draw();

				if(m_width.bottom)
				{
					if(m_width.left)
						m_corners.bottom_left.draw();
					m_boders.bottom.draw();
					if(m_width.right)
						m_corners.bottom_right.draw();
				}
			}
		}
	}
}