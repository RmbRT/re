#include "Scene.hpp"

namespace re
{
	Scene::Scene() : root(*this)	{ }

	SceneNode &Scene::getRoot()
	{
		return root;
	}
	const SceneNode &Scene::getRoot() const
	{
		return root;
	}
}