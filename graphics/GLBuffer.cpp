#include "GLBuffer.hpp"
#include "OpenGL.hpp"
#include "Vertex.hpp"
#include "../modules/GLObjectManager.hpp"

re::uint32 re::graphics::GLBuffer::bound = 0;

namespace re
{
	namespace graphics
	{
		inline size_t getSize(AttribLocation location)
		{
			switch(location)
			{
			case AttribLocation::AL_POSITION:
				{
					return 3;
				} break;
			case AttribLocation::AL_NORMAL:
				{
					return 3;
				} break;
			case AttribLocation::AL_COLOR:
				{
					return 4;
				} break;
			case AttribLocation::AL_TEXCOORD:
				{
					return 2;
				} break;

			}
		}
		inline GLenum isNormalized(AttribLocation location)
		{
			switch(location)
			{
			case AttribLocation::AL_POSITION:
				{
					return GL_FALSE;
				} break;
			case AttribLocation::AL_NORMAL:
				{
					return GL_TRUE;
				} break;
			case AttribLocation::AL_COLOR:
				{
					return GL_FALSE;
				} break;
			case AttribLocation::AL_TEXCOORD:
				{
					return GL_FALSE;
				} break;
			}
		}

		GLBuffer::GLBuffer(AttribLocation location) : id(0), location(location)	{	}

		GLBuffer::GLBuffer(GLBuffer &&move) : id(move.id), location(move.location)
		{
			move.id = 0;
		}

		GLBuffer &GLBuffer::operator=(GLBuffer &&move)
		{
			if(this == &move)
				return *this;

			dealloc();

			id = move.id;
			location = move.location;
			move.id = 0;
			
			return *this;
		}

		GLBuffer::~GLBuffer()
		{
			dealloc();
		}
		void GLBuffer::alloc()
		{
			if (!id)
			{
				RE_OGL(glGenBuffers(1, &id));
				RE_ASSERT(id != 0);
			}
			modules::GLObjectManager::GetInst()->onAlloc(this, id);
		}
		void GLBuffer::dealloc()
		{
			if(id)
			{
				modules::GLObjectManager::GetInst()->onDestroy(this, id);
				RE_OGL(glDeleteBuffers(1, &id));
				if(bound == id)
					bound = 0;
				id = 0;
			}
		}
		void GLBuffer::bind()
		{
			if(bound != id && id != 0)
			{
				RE_OGL(glBindBuffer(GL_ARRAY_BUFFER, id));
				bound = id;
			}
		}
		void GLBuffer::indexBind()
		{
			RE_OGL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id));
		}
		uint32 GLBuffer::getId() const
		{
			return id;
		}
		void GLBuffer::data(size_t size, const void* data, int usage)
		{
			if(!id)
				alloc();
			bind();
			switch(location)
			{
			case AttribLocation::AL_POSITION:
				{
					size *= sizeof(decltype(Vertex::position));
				} break;
			case AttribLocation::AL_NORMAL:
				{
					size *= sizeof(decltype(Vertex::normal));
				} break;
			case AttribLocation::AL_COLOR:
				{
					size *= sizeof(decltype(Vertex::color));
				} break;
			case AttribLocation::AL_TEXCOORD:
				{
					size *= sizeof(decltype(Vertex::texture));
				} break;
			}
			RE_OGL(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
			RE_OGL(glEnableVertexAttribArray((uint)location));
				
			RE_OGL(glVertexAttribPointer((uint)location, getSize(location), GL_FLOAT, isNormalized(location), 0, 0));
		}
		void GLBuffer::unbind()
		{
			if(bound)
			{
				RE_OGL(glBindBuffer(GL_ARRAY_BUFFER, 0));
				bound = 0;
			}
		}
	}
}