#include "RenderBuffer.hpp"
#include "OpenGL.hpp"
#include "../LogFile.hpp"
#include "../modules/GLObjectManager.hpp"

re::uint32 re::graphics::RenderBuffer::bound = 0;

namespace re
{
	namespace graphics
	{
		RenderBuffer::RenderBuffer(): id(0), width(0), height(0)	{	}
		RenderBuffer::~RenderBuffer()
		{
			destroy();
		}

		RenderBuffer::RenderBuffer(RenderBuffer &&move) : id(move.id), width(move.width), height(move.height) { move.id = 0; move.width = move.height = 0; }

		void RenderBuffer::alloc()
		{
			if(!id)
				return;
			RE_OGL(glGenRenderbuffers(1, &id));
			modules::GLObjectManager::GetInst()->onAlloc(this, id);
		}

		void RenderBuffer::destroy()
		{
			if(!id)
				return;
			if(isBound())
				unbind();
			modules::GLObjectManager::GetInst()->onDestroy(this, id);
			RE_OGL(glDeleteRenderbuffers(1, &id));
			id = 0;
			width = 0;
			height = 0;
		}

		void RenderBuffer::setSize(uint32 width, uint32 height)
		{
			RE_ASSERT(id != 0);
			if(this->width == width && this->height == height)
				return;
			bind();
			RE_OGL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height));
		}
		
		uint32 RenderBuffer::getWidth() const
		{
			return width;
		}
		uint32 RenderBuffer::getHeight() const
		{
			return height;
		}

		uint32 RenderBuffer::getId() const
		{
			return id;
		}

		void RenderBuffer::bind() const
		{
			if(!isBound())
			{
				RE_ASSERT(id != 0);
				RE_OGL(glBindRenderbuffer(GL_RENDERBUFFER, id));
				bound = 0;
			}
		}

		bool RenderBuffer::isBound() const
		{
			return bound == id;
		}

		void RenderBuffer::unbind()
		{
			if(bound)
			{
				RE_OGL(glBindRenderbuffer(GL_RENDERBUFFER, 0));
				bound = 0;
			}
		}
	}
}