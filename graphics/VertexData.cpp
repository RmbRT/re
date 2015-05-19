#include "VertexData.hpp"
#include "OpenGL.hpp"

re::uint re::graphics::VertexData::bound = 0;

#include "../LogFile.hpp"
#include "../modules/GLObjectManager.hpp"

namespace re
{
	namespace graphics
	{
		VertexData::VertexData(RenderMode mode, AllocationStrategy strat) :
			id(0), coords(AttribLocation::AL_POSITION),
			texCoords(AttribLocation::AL_TEXCOORD),
			colors(AttribLocation::AL_COLOR),
			normals(AttribLocation::AL_NORMAL),
			mode(mode), strat(strat), aabb(math::empty), data() { }

		VertexData::VertexData(VertexData &&move):
			id(move.id), coords(std::move(move.coords)),
			texCoords(std::move(move.texCoords)),
			colors(std::move(move.colors)),
			normals(std::move(move.normals)),
			mode(move.mode), strat(move.strat), aabb(move.aabb), data(std::move(move.data))
		{
			move.id = 0;
		}

		VertexData::~VertexData()
		{
			dealloc();
		}
		
		VertexData &VertexData::operator=(VertexData &&move)
		{
			if(this == &move)
				return *this;
			
			dealloc();

			id = move.id;
			coords = std::move(move.coords);
			texCoords = std::move(move.texCoords);
			colors = std::move(move.colors);
			normals = std::move(move.normals);
			mode = move.mode;
			strat = move.strat;
			aabb = move.aabb;
			data = std::move(move.data);

			move.id = 0;

			return *this;
		}

		void VertexData::alloc()
		{
			if(id)
				return;
			RE_OGL(glGenVertexArrays(1, &id));
			modules::GLObjectManager::GetInst()->onAlloc(this, id);
		}
		void VertexData::dealloc()
		{
			if(id)
			{
				modules::GLObjectManager::GetInst()->onDestroy(this, id);
				if(bound == id)
					unbind();
				coords.dealloc();
				texCoords.dealloc();
				colors.dealloc();
				normals.dealloc();

				RE_OGL(glDeleteVertexArrays(1, &id));
				id = 0;
			}
		}
		void VertexData::bind() const
		{
			if(bound == id)
				return;
			RE_ASSERT(id);
			bound = id;
			RE_OGL(glBindVertexArray(id));
		}
		void VertexData::unbind()
		{
			if(bound)
			{
				RE_OGL(glBindVertexArray(0));
				bound = 0;
			}
		}

		bool VertexData::isBound() const
		{
			return id == bound;
		}

		void VertexData::setData(const Vertex *vdata, int vcount)
		{
			math::fvec3 * ppos = new math::fvec3[vcount];
			math::fvec4 * pcol = new math::fvec4[vcount];
			math::fvec3 * pnrm = new math::fvec3[vcount];
			math::fvec2 * ptex = new math::fvec2[vcount];

			if(!id)
				alloc();

			bind();
			aabb.setToEmpty();
			data.clear();
			data.reserve(vcount);

			for(int i = 0; i<vcount; i++)
			{
				const Vertex & vert = vdata[i];
				data.push_back(vert);
				ppos[i] = vert.position;
				pcol[i] = vert.color;
				pnrm[i] = vert.normal;
				ptex[i] = vert.texture;
				aabb |= vert.position;
			}
			
			GLenum mode = GLU_INVALID_ENUM;
			switch(strat)
			{
			case AllocationStrategy::AS_STATIC: mode = GL_STATIC_DRAW; break;
			case AllocationStrategy::AS_DYNAMIC: mode = GL_DYNAMIC_DRAW; break;
			}
			coords.data(vcount, ppos, mode);
			texCoords.data(vcount, ptex, mode);
			colors.data(vcount, pcol, mode);
			normals.data(vcount, pnrm, mode);

			delete [] ppos;
			delete [] pcol;
			delete [] pnrm;
			delete [] ptex;
		}

		void VertexData::reloadData()
		{
			size_t vcount = data.size();
			math::fvec3 * ppos = new math::fvec3[vcount];
			math::fvec4 * pcol = new math::fvec4[vcount];
			math::fvec3 * pnrm = new math::fvec3[vcount];
			math::fvec2 * ptex = new math::fvec2[vcount];
			
			aabb.setToEmpty();

			for(size_t i = 0; i<vcount; i++)
			{
				Vertex & vert = data[i];
				ppos[i] = vert.position;
				pcol[i] = vert.color;
				pnrm[i] = vert.normal;
				ptex[i] = vert.texture;
				aabb |= vert.position;
			}
			
			GLenum mode = GLU_INVALID_ENUM;
			switch(strat)
			{
			case AllocationStrategy::AS_STATIC: mode = GL_STATIC_DRAW; break;
			case AllocationStrategy::AS_DYNAMIC: mode = GL_DYNAMIC_DRAW; break;
			default: break;
			}

			coords.data(vcount, ppos, mode);
			texCoords.data(vcount, ptex, mode);
			colors.data(vcount, pcol, mode);
			normals.data(vcount, pnrm, mode);

			delete [] ppos;
			delete [] pcol;
			delete [] pnrm;
			delete [] ptex;
		}

		void VertexData::draw() const
		{
			GLenum glenum;
			switch(mode)
			{
			case RenderMode::RM_LINE_STRIP: glenum = GL_LINE_STRIP; break;
			case RenderMode::RM_LINES: glenum = GL_LINES; break;
			case RenderMode::RM_TRIANGLES: glenum = GL_TRIANGLES; break;
			case RenderMode::RM_TRIANGLE_STRIP: glenum = GL_TRIANGLE_STRIP; break;
			case RenderMode::RM_POINTS: glenum = GL_POINTS; break;
			case RenderMode::RM_QUADS: glenum = GL_QUADS; break;
			case RenderMode::RM_QUAD_STRIP: glenum = GL_QUAD_STRIP; break;
			case RenderMode::RM_TRIANGLE_FAN: glenum = GL_TRIANGLE_FAN; break;
			default: RE_ASSERTION_FAILURE("INVALID ENUM VALUE"); break;
			}
			bind();
			RE_OGL("Previous error");
			RE_OGL(glDrawArrays(glenum, 0, data.size()));
		}

		RenderMode VertexData::getRenderMode() const
		{
			return mode;
		}
		AllocationStrategy VertexData::getAllocationStrategy() const
		{
			return strat;
		}
		const math::fAABB &VertexData::getAABB() const
		{
			return aabb;
		}
		std::vector<Vertex> &VertexData::getVertices()
		{
			return data;
		}
		const std::vector<Vertex> &VertexData::getVertices() const
		{
			return data;
		}
	}
}