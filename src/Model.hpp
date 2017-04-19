#ifndef __re_model_hpp_defined
#define __re_model_hpp_defined

#include "types.hpp"
#include "graphics/Material.hpp"
#include "graphics/gl/ShaderProgram.hpp"
#include "graphics/gl/Texture.hpp"
#include "graphics/gl/VertexArray.hpp"
#include "math/AxisAlignedBoundingBox.hpp"

namespace re
{
	class Model
	{
		Shared<graphics::Material> m_material;
		Shared<graphics::gl::ShaderProgram> m_shader;
		Shared<graphics::gl::VertexArrayBase> m_vertex_data;
		Shared<graphics::gl::Texture> m_texture;
	public:
		Model(
			Shared<graphics::Material> mat,
			Shared<graphics::gl::ShaderProgram> shader,
			Shared<graphics::gl::VertexArrayBase> vertex_data,
			Shared<graphics::gl::Texture> texture);

		/** Passes the material properties to the shader. This binds the shader. */
		void passMaterial() const;
		/** Draws the VertexData. */
		void draw(math::fmat4x4_t const& mvp) const;

		/** Returns the BoundingBox of the VertexData. */
		math::faabb_t const& aabb() const;
		/** Returns the VertexData of this Model. */
		Shared<graphics::gl::VertexArrayBase> const& vertex_data() const&;
		void setVertexData(Shared<graphics::gl::VertexArrayBase> vertex_data);
		Shared<graphics::Material> const& material() const;
		void setMaterial(Shared<graphics::Material> material);
		Shared<graphics::gl::ShaderProgram> const& shader() const;
		void setShader(Shared<graphics::gl::ShaderProgram> shader);
		Shared<graphics::gl::Texture> const& texture() const;
		void setTexture(Shared<graphics::gl::Texture> texture);
	};
}




#endif
