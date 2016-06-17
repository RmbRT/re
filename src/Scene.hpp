#ifndef __re_scene_hpp_defined
#define __re_scene_hpp_defined

#include "SceneNode.hpp"
#include "types.hpp"
#include "defines.hpp"

namespace re
{
	class Scene
	{
		SceneNode root;
	public:
		Scene();

		SceneNode &getRoot();
		const SceneNode &getRoot() const;
	};
}

#endif