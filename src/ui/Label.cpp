#include "Label.hpp"
#include "../graphics/gl/OpenGL.hpp"

namespace re
{
	namespace ui
	{
		Label::Label():
			m_font(),
			m_text(),
			m_vertex_array(
				graphics::gl::BufferAccess::Static,
				graphics::gl::BufferUsage::Draw),
			m_settings(),
			m_pen_position()
		{
		}

		Label::Label(Label &&move):
			m_font(std::move(move.m_font)),
			m_vertex_array(std::move(move.m_vertex_array)),
			m_text(std::move(move.m_text)),
			m_settings(std::move(move.m_settings)),
			m_pen_position(std::move(move.m_pen_position))
		{
		}

		Label& Label::operator=(Label &&move)
		{
			if(this == &move)
				return *this;
			m_font = std::move(move.m_font);
			m_vertex_array = std::move(move.m_vertex_array);
			m_text = std::move(move.m_text);
			m_settings = std::move(move.m_settings);
			m_pen_position = std::move(move.m_pen_position);

			return *this;
		}

		void Label::set_font(
			Shared<Font> const& font)
		{
			this->m_font = font;
		}
		Shared<Font> const& Label::font() const
		{
			return m_font;
		}
		void Label::set_text(
			string32_t const& text)
		{
			this->m_text = text;
		}
		string32_t const& Label::text() const
		{
			return m_text;
		}

		void Label::update()
		{
			if(m_font)
				m_font->compile(
					m_text,
					m_settings,
					m_pen_position,
					m_vertex_array);
		}

		VertexArray const& Label::vertex_array() const
		{
			return m_vertex_array;
		}

		math::fvec2_t Label::size() const
		{
			if(m_text.empty())
				return math::fvec2_t(0,0);
			else
			{
				RE_DBG_ASSERT(m_vertex_array.exists());
				return math::fvec2_t(m_vertex_array.aabb().size());
			}
		}
		math::fvec2_t Label::min_position() const
		{
			if(m_vertex_array.exists())
				return math::fvec2_t(m_vertex_array.aabb().min());
			else return math::fvec2_t(0,0);
		}

		void Label::draw()
		{
			RE_OGL(glEnable(GL_BLEND));
			RE_OGL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
			m_font->texture()->bind();
			m_vertex_array.draw();
			RE_OGL(glDisable(GL_BLEND));
		}

		FontSettings &Label::font_settings()
		{
			return m_settings;
		}
		const FontSettings &Label::font_settings() const
		{
			return m_settings;
		}

	}
}