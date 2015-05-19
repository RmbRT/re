#ifndef __re_globjectmanager_hpp_defined
#define __re_globjectmanager_hpp_defined

#include "../types.hpp"
#include "../Singleton.hpp"
#include "../graphics/FrameBuffer.hpp"
#include "../graphics/GLBuffer.hpp"
#include "../graphics/RenderBuffer.hpp"
#include "../graphics/VertexData.hpp"
#include "../graphics/Texture.hpp"
#include "../graphics/ShaderProgram.hpp"
#include <vector>
#include "../LogFile.hpp"


namespace re
{
	namespace modules
	{
		class GLObjectManager : public Singleton<GLObjectManager>
		{
			std::vector<uint32> buffers;
			std::vector<uint32> shaderPrograms;
			std::vector<uint32> frameBuffers;
			std::vector<uint32> renderBuffers;
			std::vector<uint32> textures;
			std::vector<uint32> vaos;
		public:
			~GLObjectManager()
			{
				LogFile::GetInst()->writefln(
					__FUNCTION__"\n"
					"allocated buffers: %i\n"
					"allocated shader programs: %i\n"
					"allocated frame buffers: %i\n"
					"allocated render buffers: %i\n"
					"allocated textures: %i\n"
					"allocated vertex array objects: %i",
					buffers.size(),
					shaderPrograms.size(),
					frameBuffers.size(),
					renderBuffers.size(),
					textures.size(),
					vaos.size());
			}

			void onAlloc(const graphics::FrameBuffer *, uint32 id);
			void onDestroy(const graphics::FrameBuffer *, uint32 id);
			void onAlloc(const graphics::GLBuffer *, uint32 id);
			void onDestroy(const graphics::GLBuffer *, uint32 id);
			void onAlloc(const graphics::RenderBuffer *, uint32 id);
			void onDestroy(const graphics::RenderBuffer *, uint32 id);
			void onAlloc(const graphics::ShaderProgram *, uint32 id);
			void onDestroy(const graphics::ShaderProgram *, uint32 id);
			void onAlloc(const graphics::Texture *, uint32 id);
			void onDestroy(const graphics::Texture *, uint32 id);
			void onAlloc(const graphics::VertexData *, uint32 id);
			void onDestroy(const graphics::VertexData *, uint32 id);
		};
	}
}


#endif