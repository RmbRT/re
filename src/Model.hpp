#ifndef __re_model_hpp_defined
#define __re_model_hpp_defined

#include "types.hpp"
#include "graphics/Material.hpp"
#include "graphics/ShaderProgram.hpp"
#include "graphics/gl/Texture.hpp"
#include "graphics/gl/VertexArray.hpp"
#include "math/AxisAlignedBoundingBox.hpp"
namespace re
{
	class Model
	{
		Shared<graphics::Material> material;
		Shared<graphics::gl::ShaderProgram> shader;
		Shared<graphics::gl::VertexArrayBase> vertexData;
		Shared<graphics::gl::Texture> texture;
	public:
		Model(strong_handle<graphics::Material> mat, strong_handle<graphics::ShaderProgram> shader, strong_handle<graphics::gl::VertexArrayBase> vertexData, strong_handle<graphics::Texture> texture);



		/** Passes the material properties to the shader. This binds the shader. */
		void passMaterial() const;
		/** Draws the VertexData. */
		void draw(const math::fmat4x4 &mvp) const;
	
		/** Returns the BoundingBox of the VertexData. */
		const math::fAABB &getAABB() const;
		/** Returns the VertexData of this Model. */
		strong_handle<graphics::VertexData> getVertexData() const;
		void setVertexData(strong_handle<graphics::gl::VertexArrayBase> vertexData);
		strong_handle<graphics::Material> getMaterial() const;
		void setMaterial(strong_handle<graphics::Material> material);
		strong_handle<graphics::ShaderProgram> getShader() const;
		void setShader(strong_handle<graphics::ShaderProgram> shader);
		strong_handle<graphics::Texture> getTexture() const;
		void setTexture(strong_handle<graphics::Texture> texture);
	};
}




#endif