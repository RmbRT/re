#include "Renderer.hpp"
#include "graphics/gl/OpenGL.hpp"
#include "Scene.hpp"
#include "SceneNode.hpp"

#include "LogFile.hpp"

namespace re
{
	Renderer::Renderer(
		NotNull<graphics::gl::ShaderProgram> shader,
		NotNull<Scene> scene,
		NotNull<graphics::Window> window,
		NotNull<Camera> camera,
		graphics::gl::ShaderProgram::uniform_t transform_uniform):
		shader(shader),
		transform_uniform(transform_uniform),
		scene(scene),
		window(window),
		camera(camera),
		projection(
			math::fmat4x4_t::perspective(
				math::deg(65),
				2,
				2,
				0,
				1000.f))
	{
	}

	Renderer::Renderer(
		NotNull<graphics::gl::ShaderProgram> shader,
		NotNull<Scene> scene,
		NotNull<graphics::Window> window,
		NotNull<Camera> camera,
		string8_t const& transform_uniform):
		shader(shader),
		transform_uniform(
			shader->get_uniform(transform_uniform.c_str())),
		scene(scene),
		window(window),
		camera(camera),
		projection(
			math::fmat4x4_t::perspective(
				math::deg(65),
				2,
				2,
				0,
				1000.f))
	{
	}

	void Renderer::render()
	{
		RE_DBG_ASSERT(window->context().current());
		shader->use();

		math::fmat4x4_t camera_mat(camera->view_matrix());

		render(scene->getRoot(), projection * camera_mat);
	}

	void Renderer::render(
		SceneNode const& node,
		math::fmat4x4_t const& camera_mat)
	{
		math::fmat4x4_t mvp = camera_mat * node.getTransformation();

		if(auto model = node.getModel())
		{
			model->draw(mvp);
		}
		if(!node.isLeaf())
		{
			auto _node = node.firstChild();
			do render(*_node, mvp);
			while(_node = _node->nextSibling());
		}
	}

	void Renderer::setTransformUniform(
		graphics::gl::ShaderProgram::uniform_t uniform)
	{
		transform_uniform = uniform;
	}

	void Renderer::setTransformUniform(
		string8_t const& name)
	{
		transform_uniform = shader->get_uniform(name.c_str());
	}

	void Renderer::setProjection(
		math::fmat4x4_t const& projection)
	{
		this->projection = projection;
	}
}