#include "RenderSession.hpp"

namespace re
{
	namespace graphics
	{
		RenderSession::RenderSession():
			m_matrices(),
			m_colors(),
			m_passed_color(),
			m_passed_matrix(math::fmat4x4_t::kIdentity),
			m_shader(nullptr),
			m_color_uniform(0),
			m_mvp_uniform(0)
		{
		}

		void RenderSession::push_matrix(
			math::fmat4x4_t const& mat)
		{
			m_matrices.push(mat);
		}
		void RenderSession::pop_matrix()
		{
			m_matrices.pop();
		}
		math::fmat4x4_t const& RenderSession::matrix() const
		{
			return m_matrices.top();
		}
		math::fvec4_t const& RenderSession::color() const
		{
			return m_colors.top();
		}
		void RenderSession::push_color(
			math::fvec4_t const& color)
		{
			m_colors.push(color);
		}
		void RenderSession::pop_color()
		{
			m_colors.pop();
		}
		void RenderSession::set_shader(
			Shared<gl::ShaderProgram> const& shader,
			gl::ShaderProgram::uniform_t color_uniform,
			gl::ShaderProgram::uniform_t mvp_uniform)
		{
			m_shader = shader;
			m_mvp_uniform = mvp_uniform;
			m_color_uniform = color_uniform;
		}

		void RenderSession::pass_values() const
		{
			RE_DBG_ASSERT(m_shader && "cannot pass values if no shader was set.");
			RE_DBG_ASSERT(!m_matrices.empty() && "set up a mvp matrix before passing values.");
			RE_DBG_ASSERT(!m_colors.empty() && "set up a color before passing a value.");

			if(m_passed_color != color())
			{
				m_passed_color = color();
				m_shader->set_uniform(m_color_uniform, m_passed_color);
			}
			if(m_passed_matrix != matrix())
			{
				m_passed_matrix = matrix();
				m_shader->set_uniform(m_mvp_uniform, m_passed_matrix);
			}
		}
	}
}