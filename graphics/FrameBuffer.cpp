#include "FrameBuffer.hpp"
#include "OpenGL.hpp"
#include "../LogFile.hpp"
#include "../modules/GLObjectManager.hpp"

re::uint32 re::graphics::FrameBuffer::bound = 0;

namespace re
{
	namespace graphics
	{
		FrameBuffer::FrameBuffer(): id(0), bufferColor(), bufferDepth(), bufferStencil(), bufferDepthStencil()	{	}
		FrameBuffer::~FrameBuffer()
		{
			destroy();
		}

		FrameBuffer::FrameBuffer(FrameBuffer &&move): id(move.id), bufferColor(std::move(move.bufferColor)), bufferDepth(std::move(move.bufferDepth)), bufferStencil(std::move(move.bufferStencil)), bufferDepthStencil(std::move(move.bufferDepthStencil)) { move.id = 0; }

		void FrameBuffer::alloc()
		{
			destroy();
			RE_OGL(glGenFramebuffers(1, &id));
			modules::GLObjectManager::GetInst()->onAlloc(this, id);
			bind();
		}


		void FrameBuffer::destroy()
		{
			if(!id)
				return;

			modules::GLObjectManager::GetInst()->onDestroy(this, id);

			if(isBound())
				unbind();
			detachBufferColor();
			detachBufferDepth();
			detachBufferStencil();
			detachBufferDepthStencil();
			RE_OGL(glDeleteFramebuffers(1, &id));
			id = 0;
		}

		void FrameBuffer::setSize(uint32 width, uint32 height)
		{
			RE_ASSERT(id != 0);
			if(bufferColor.getId())
				bufferColor.setBounds(width, height);
			if(bufferDepth.getId())
				bufferDepth.setSize(width, height);
			if(bufferStencil.getId())
				bufferStencil.setSize(width, height);
			if(bufferDepthStencil.getId())
				bufferDepthStencil.setSize(width, height);
			this->width = width;
			this->height = height;
		}

		uint32 FrameBuffer::getWidth() const
		{
			return width;
		}
		uint32 FrameBuffer::getHeight() const
		{
			return height;
		}

		const Texture &FrameBuffer::getBufferColor() const
		{
			return bufferColor;
		}
		const RenderBuffer &FrameBuffer::getBufferDepth() const
		{
			return bufferDepth;
		}
		const RenderBuffer &FrameBuffer::getBufferStencil() const
		{
			return bufferStencil;
		}
		const RenderBuffer &FrameBuffer::getBufferDepthStencil() const
		{
			return bufferDepthStencil;
		}

		Texture &FrameBuffer::getBufferColor()
		{
			return bufferColor;
		}
		RenderBuffer &FrameBuffer::getBufferDepth()
		{
			return bufferDepth;
		}
		RenderBuffer &FrameBuffer::getBufferStencil()
		{
			return bufferStencil;
		}
		RenderBuffer &FrameBuffer::getBufferDepthStencil()
		{
			return bufferDepthStencil;
		}



		void FrameBuffer::attachBufferColor(void)
		{
			if(bufferColor.getId())
				return;
			bufferColor.alloc(2);
			
			/*Set up the parameters for the Color Buffer.*/
			auto & params = bufferColor.getParameters();
			params.generate_mipmap = false;
			params.min_filter = Filter::F_NEAREST;
			params.mag_filter = Filter::F_NEAREST;
			//bufferColor.updateParameters();
			bufferColor.setBounds(width, height);
			RE_ASSERT(bufferColor.exists());
			bind();
			bufferColor.bind();
			bufferColor.setData(Bitmap(ColorChannel::FLOAT4, 256, 256));
			RE_OGL("");
			RE_OGL(glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, bufferColor.getId(), 0));
		}
		bool FrameBuffer::hasBufferColor(void) const
		{
			return bufferColor.getId();
		}
		void FrameBuffer::detachBufferColor(void)
		{
			if(!hasBufferColor())
				return;
			bind();
			RE_OGL(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 0, 0));
			bufferColor.destroy();
		}





		void FrameBuffer::attachBufferDepth(void)
		{
			if(hasBufferDepth())
				return;
			bufferDepth.alloc();
			bufferDepth.setSize(width, height);
			bind();
			RE_OGL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, bufferDepth.getId()));
		}
		bool FrameBuffer::hasBufferDepth(void) const
		{
			return bufferDepth.getId();
		}
		void FrameBuffer::detachBufferDepth()
		{
			if(!hasBufferDepth())
				return;
			bind();
			RE_OGL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0));
			bufferDepth.destroy();
		}




		void FrameBuffer::attachBufferStencil(void)
		{
			if(hasBufferStencil())
				return;

			bufferStencil.alloc();
			bufferStencil.setSize(width, height);

			bind();
			RE_OGL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, bufferStencil.getId()));
		}
		bool FrameBuffer::hasBufferStencil(void) const
		{
			return bufferStencil.getId();
		}
		void FrameBuffer::detachBufferStencil()
		{
			if(!hasBufferStencil())
				return;
			bind();
			RE_OGL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, 0));
			bufferStencil.destroy();
		}





		void FrameBuffer::attachBufferDepthStencil(void)
		{
			if(hasBufferDepthStencil())
				return;
			bufferDepthStencil.alloc();
			bufferDepthStencil.setSize(width, height);
			bind();
			RE_OGL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, bufferDepthStencil.getId()));
		}
		bool FrameBuffer::hasBufferDepthStencil(void) const
		{
			return bufferDepthStencil.getId();
		}
		void FrameBuffer::detachBufferDepthStencil()
		{
			if(!hasBufferDepthStencil())
				return;
			bind();
			RE_OGL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, 0));
		}


		bool FrameBuffer::exists() const
		{
			return id && glIsFramebuffer(id);
		}


		void FrameBuffer::bind()
		{
			if(!id || isBound())
				return;
			bound = id;
			RE_OGL(glBindFramebuffer(GL_FRAMEBUFFER, id));
		}

		bool FrameBuffer::isBound() const
		{
			return bound == id && id != 0;
		}

		void FrameBuffer::unbind()
		{
			if(bound)
			{
				RE_OGL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
				bound = 0;
			}
		}
	}
}