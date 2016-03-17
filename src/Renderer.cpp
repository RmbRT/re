#include "Renderer.hpp"
#include "graphics\OpenGL.hpp"
#include "Scene.hpp"
#include "SceneNode.hpp"

#include "LogFile.hpp"

namespace re
{
	Renderer::Renderer(notnull<graphics::ShaderProgram> shader, notnull<Scene> scene, notnull<Window> window, notnull<Camera> camera, graphics::ShaderProgram::uniform_t transform_uniform): shader(shader), transform_uniform(transform_uniform), scene(scene), window(window), camera(camera), projection(math::fmat4x4::perspective(math::deg(65), 2,2, 0, 1000.f)) {}
	Renderer::Renderer(notnull<graphics::ShaderProgram> shader, notnull<Scene> scene, notnull<Window> window, notnull<Camera> camera, const string &transform_uniform): shader(shader), transform_uniform(shader->getUniform(transform_uniform.c_str())), scene(scene), window(window), camera(camera), projection(math::fmat4x4::perspective(math::deg(65), 2,2, 0, 1000.f)) {}
	
	void Renderer::render()
	{
		window->makeContextCurrent();
		shader->use();
		
		math::fmat4x4 camera_mat(camera->getViewMatrix());
		
		render(scene->getRoot(), projection * camera_mat);
	}

	void Renderer::render(const SceneNode &node, math::fmat4x4 &camera_mat)
	{
		math::fmat4x4 mvp = camera_mat * node.getTransformation();

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

	void Renderer::setTransformUniform(graphics::ShaderProgram::uniform_t uniform)
	{
		transform_uniform = uniform;
	}

	void Renderer::setTransformUniform(const string &name)
	{
		transform_uniform = shader->getUniform(name.c_str());
	}

	void Renderer::setProjection(const math::fmat4x4 &projection)
	{
		this->projection = projection;
	}
}