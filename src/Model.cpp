#include "Model.hpp"

namespace re
{
	Model::Model(strong_handle<graphics::Material> mat, strong_handle<graphics::ShaderProgram> shader, strong_handle<graphics::VertexData> vertexData, strong_handle<graphics::Texture> texture) : material(mat), shader(shader), vertexData(vertexData), texture(texture) { }
	void Model::passMaterial() const
	{
		shader->use();
		shader->setUniform("RE_MAT_AMBIENT", material->ambient);
		shader->setUniform("RE_MAT_DIFFUSE", material->diffuse);
		shader->setUniform("RE_MAT_SPECULAR", material->specular);
		shader->setUniform("RE_MAT_SHININESS", material->shininess);
		shader->setUniform("texture_color", 0);
	}
	const math::fAABB &Model::getAABB() const
	{
		return vertexData->getAABB();
	}
	strong_handle<graphics::VertexData> Model::getVertexData() const
	{
		return vertexData;
	}
	void Model::draw(const math::fmat4x4 &mvp) const
	{
		passMaterial();
		texture->bind();
		shader->setUniform("RE_MVP", mvp);
		vertexData->bind();
		vertexData->draw();
	}
}