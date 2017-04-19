#ifndef __re_renderer_hpp_defined
#define __re_renderer_hpp_defined

#include "graphics/gl/ShaderProgram.hpp"
#include "graphics/Window.hpp"
#include "types.hpp"
#include "Camera.hpp"
#include "Scene.hpp"

#include "ui/UIView.hpp"
#include "Projection.hpp"

namespace re
{
	class Renderer
	{
		NotNull<graphics::gl::ShaderProgram> shader;

		graphics::gl::ShaderProgram::uniform_t transform_uniform;

		NotNull<Scene> scene;
		NotNull<graphics::Window> window;
		NotNull<Camera> camera;
		math::fmat4x4_t projection;


	public:
		Renderer(
			NotNull<graphics::gl::ShaderProgram> shader,
			NotNull<Scene> scene,
			NotNull<graphics::Window> window,
			NotNull<Camera> camera,
			graphics::gl::ShaderProgram::uniform_t transform_uniform);
		Renderer(
			NotNull<graphics::gl::ShaderProgram> shader,
			NotNull<Scene> scene,
			NotNull<graphics::Window> window,
			NotNull<Camera> camera,
			string8_t const& transform_uniform);
		NotNull<graphics::gl::ShaderProgram> getShader();

		void setTransformUniform(
			graphics::gl::ShaderProgram::uniform_t uniform);
		void setTransformUniform(
			string8_t const& name);

		void setProjection(
			math::fmat4x4_t const& projection);

		virtual void render();
		virtual void render(
			SceneNode const& node,
			math::fmat4x4_t const& camera_mat);
	};
}

#endif