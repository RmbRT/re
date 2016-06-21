#ifndef __re_mesh_hpp_defined
#define __re_mesh_hpp_defined

#include "../types.hpp"
#include "../defines.hpp"
#include "../graphics/Vertex.hpp"
#include "../graphics/VertexData.hpp"
#include "../graphics/ShaderProgram.hpp"
#include "../graphics/Material.hpp"
#include "../math/Angle.hpp"
#include "../math/AxisAlignedBoundingBox.hpp"
#include "../math/Vector.hpp"
#include "../math/Matrix.hpp"
#include "../math/Ray.hpp"
#include <memory>

namespace re
{
	namespace world
	{
		class Mesh
		{
			std::shared_ptr<graphics::ShaderProgram> shader;
			std::shared_ptr<graphics::Material> material;
			std::shared_ptr<graphics::VertexData> vertexData;
			
			/** The BoundingBox containing the boundaries of the mesh. */
			mutable math::fAABB boundingBox;
		public:

			/** Calculates the AxisAlignedBoundingBox of this Mesh. */
			void calcBoundingBox() const;


			/** Returns the AxisAlignedBoundingBox of this Mesh.
			@note: This does not calculate the BoundingBox. Call @[re::world::Mesh::calcBoundingBox]befor. */
			const math::fAABB &getBoundingBox() const;
			/** Returns the ShaderProgram that is used by this Mesh. */
			const std::shared_ptr<graphics::ShaderProgram> &getShader() const;
			/** Returns the VertexData used by the Mesh. */
			const std::shared_ptr<graphics::VertexData> &getVertexData() const;

			/** Creates a wireframed version of the Mesh. */
			std::shared_ptr<Mesh> createWireFrame() const;


		};
	}
}

#endif