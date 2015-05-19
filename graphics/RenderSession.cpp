#include "RenderSession.hpp"

namespace re
{
	namespace graphics
	{
		RenderSession::RenderSession() : matrices(), colors(), passed_color(), passed_matrix(math::fmat4x4::IDENTITY), shader(nullptr), color_uniform(0), mvp_uniform(0) { }
		void RenderSession::push_matrix(const math::fmat4x4 &mat)
		{
			matrices.push(mat);
		}
		void RenderSession::pop_matrix()
		{
			matrices.pop();
		}
		const math::fmat4x4 &RenderSession::matrix() const
		{
			return matrices.top();
		}
		const math::fvec4 &RenderSession::color() const
		{
			return colors.top();
		}
		void RenderSession::push_color(const math::fvec4 &color)
		{
			colors.push(color);
		}
		void RenderSession::pop_color()
		{
			colors.pop();
		}
		void RenderSession::set_shader(const strong_handle<ShaderProgram> &shader, ShaderProgram::uniform_t color_uniform, ShaderProgram::uniform_t mvp_uniform)
		{
			this->shader = shader;
			this->mvp_uniform = mvp_uniform;
			this->color_uniform = color_uniform;
		}

		void RenderSession::pass_values() const
		{
			RE_ASSERT(shader && "cannot pass values if no shader was set.");
			RE_ASSERT(!matrices.empty() && "set up a mvp matrix before passing values.");
			RE_ASSERT(!colors.empty() && "set up a color before passing a value.");
			
			if(passed_color != color())
			{
				passed_color = color();
				shader->setUniform(color_uniform, passed_color);
			}
			if(passed_matrix != matrix())
			{
				passed_matrix = matrix();
				shader->setUniform(mvp_uniform, passed_matrix);
			}
		}
	}
}