#ifndef __re_renderer_hpp_defined
#define __re_renderer_hpp_defined

#include "graphics/ShaderProgram.hpp"
#include "types.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "Scene.hpp"

#include "ui/UIView.hpp"
#include "Projection.hpp"

namespace re
{
	class Renderer
	{
		NotNull<graphics::ShaderProgram> shader;
		
		graphics::ShaderProgram::uniform_t transform_uniform;
		
		NotNull<Scene> scene;
		NotNull<Window> window;
		NotNull<Camera> camera;
		math::fmat4x4 projection;


	public:
		Renderer(NotNull<graphics::ShaderProgram> shader, NotNull<Scene> scene, NotNull<Window> window, NotNull<Camera> camera, graphics::ShaderProgram::uniform_t transform_uniform);
		Renderer(NotNull<graphics::ShaderProgram> shader, NotNull<Scene> scene, NotNull<Window> window, NotNull<Camera> camera, const string &transform_uniform);
		NotNull<graphics::ShaderProgram> getShader();

		void setTransformUniform(graphics::ShaderProgram::uniform_t uniform);
		void setTransformUniform(const string &name);

		void setProjection(const math::fmat4x4 &projection);

		virtual void render();
		virtual void render(const SceneNode &node, math::fmat4x4 &camera_mat);
	};
}

#endif