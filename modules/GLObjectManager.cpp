#include "GLObjectManager.hpp"
namespace re
{
	namespace modules
	{
		void GLObjectManager::onAlloc(const graphics::FrameBuffer *, uint32 id)
		{
			frameBuffers.push_back(id);
		}
		void GLObjectManager::onDestroy(const graphics::FrameBuffer *, uint32 id)
		{
			for(auto it = frameBuffers.begin(); it!=frameBuffers.end(); it++)
				if(*it == id)
				{
					frameBuffers.erase(it);
					return;
				}
		}
		void GLObjectManager::onAlloc(const graphics::GLBuffer *, uint32 id)
		{
			buffers.push_back(id);
		}
		void GLObjectManager::onDestroy(const graphics::GLBuffer *, uint32 id)
		{
			for(auto it = buffers.begin(); it!=buffers.end(); it++)
				if(*it == id)
				{
					buffers.erase(it);
					return;
				}
		}
		void GLObjectManager::onAlloc(const graphics::RenderBuffer *, uint32 id)
		{
			renderBuffers.push_back(id);
		}
		void GLObjectManager::onDestroy(const graphics::RenderBuffer *, uint32 id)
		{
			for(auto it = renderBuffers.begin(); it!=renderBuffers.end(); it++)
				if(*it == id)
				{
					renderBuffers.erase(it);
					return;
				}
		}
		void GLObjectManager::onAlloc(const graphics::ShaderProgram *, uint32 id)
		{
			shaderPrograms.push_back(id);
		}
		void GLObjectManager::onDestroy(const graphics::ShaderProgram *, uint32 id)
		{
			for(auto it = shaderPrograms.begin(); it!=shaderPrograms.end(); it++)
				if(*it == id)
				{
					shaderPrograms.erase(it);
					return;
				}
		}
		void GLObjectManager::onAlloc(const graphics::Texture *, uint32 id)
		{
			textures.push_back(id);
		}
		void GLObjectManager::onDestroy(const graphics::Texture *, uint32 id)
		{
			for(auto it = textures.begin(); it!=textures.end(); it++)
				if(*it == id)
				{
					textures.erase(it);
					return;
				}
		}
		void GLObjectManager::onAlloc(const graphics::VertexData *, uint32 id)
		{
			vaos.push_back(id);
		}
		void GLObjectManager::onDestroy(const graphics::VertexData *, uint32 id)
		{
			for(auto it = vaos.begin(); it!=vaos.end(); it++)
				if(*it == id)
				{
					vaos.erase(it);
					return;
				}
		}
	}
}