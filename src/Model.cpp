#include "Model.hpp"

namespace re
{
	Model::Model(
		Shared<graphics::Material> mat,
		Shared<graphics::gl::ShaderProgram> shader,
		Shared<graphics::gl::VertexArrayBase> vertex_data,
		Shared<graphics::gl::Texture> texture):
		m_material(std::move(mat)),
		m_shader(std::move(shader)),
		m_vertex_data(std::move(vertex_data)),
		m_texture(std::move(texture))
	{
	}

	void Model::passMaterial() const
	{
		m_shader->use();
		m_shader->set_uniform("RE_MAT_AMBIENT", m_material->ambient);
		m_shader->set_uniform("RE_MAT_DIFFUSE", m_material->diffuse);
		m_shader->set_uniform("RE_MAT_SPECULAR", m_material->specular);
		m_shader->set_uniform("RE_MAT_SHININESS", m_material->shininess);
		m_shader->set_uniform("texture_color", 0);
	}

	Shared<graphics::gl::VertexArrayBase> const& Model::vertex_data() const&
	{
		return m_vertex_data;
	}
	void Model::draw(
		const math::fmat4x4_t &mvp) const
	{
		passMaterial();
		m_texture->bind();
		m_shader->set_uniform("RE_MVP", mvp);
		m_vertex_data->bind();
		m_vertex_data->draw();
	}
}
