#ifndef __re_vertexdata_hpp_defined
#define __re_vertexdata_hpp_defined

#include "GLBuffer.hpp"
#include "Vertex.hpp"
#include "RenderMode.hpp"
#include "../types.hpp"
#include <vector>
#include "../math/AxisAlignedBoundingBox.hpp"

namespace re
{
	namespace graphics
	{
		RE_ENUM(AllocationStrategy)
		{
			AS_STATIC,
			AS_DYNAMIC
		};

		class VertexData
		{
			uint32 id;
			std::vector<Vertex> data;
			RenderMode mode;
			AllocationStrategy strat;
			math::fAABB aabb;

			GLBuffer coords;
			GLBuffer texCoords;
			GLBuffer colors;
			GLBuffer normals;
		public:
			/*Creates a Vertex Array object. This does not allocate memory on the GPU!
			@param[in] mode: The rendering method that is used to draw the vertices.
			@param[in] strat: The allocation strategy that is used for storing the vertices.*/
			VertexData(RenderMode mode, AllocationStrategy strat);

			/*Changes ownership of the VertexData from one object to another, invalidating the old one.*/
			VertexData(VertexData &&move);

			/*Destroys a Vertex Array object. All the memory on the GPU used by it will be freed.*/
			~VertexData();

			VertexData &operator=(VertexData &&move);

			/*Allocates the Buffer on the GPU.*/
			void alloc();
			/*To prevent memory leaks, call this when the object is of no use anymore.
			Deletes the allocated memory on the GPU.*/
			void dealloc();

			/*Loads the locally stored vertex data onto the GPU.*/
			void reloadData();
			/*Sets the vertex data and loads it onto the GPU.*/
			void setData(const Vertex *vdata, int vcount);
			/*Binds the Buffer to the GPU to be used for further rendering calls.*/
			void bind() const;
			/*Unbinds the currently bound buffer.*/
			static void unbind();

			/*Checks whether the buffer is currently bound.*/
			bool isBound() const;
			
			/*Draws the buffer.*/
			void draw() const;

			/*Returns the RenderMode used by this Vertex Buffer.*/
			RenderMode getRenderMode() const;
			/*Returns the AllocationStrategy used by this Vertex Buffer.*/
			AllocationStrategy getAllocationStrategy() const;

			const math::fAABB &getAABB() const;
			/*Use to modify the Vertex data. Use reloadData() to reload onto GPU.*/
			std::vector<Vertex> &getVertices();
			/*Returns the Vertices of this VertexData.*/
			const std::vector<Vertex> &getVertices() const;

		private:
			static uint32 bound;
		};
	}
}

#endif