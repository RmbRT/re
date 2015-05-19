#ifndef __re_scenenode_hpp_defined
#define __re_scenenode_hpp_defined

#include "math/Vector.hpp"
#include "math/Matrix.hpp"
#include <vector>
#include "types.hpp"
#include <memory>
#include "Model.hpp"
#include "defines.hpp"

namespace re
{
	/*The base scene node class used for representing entities in a scene.
	It has a tree-based layout.*/
	class SceneNode
	{	friend class Scene;

		/*The Scene this SceneNode belongs to.*/
		unsafe<Scene> scene;
		/*The SceneNode this SceneNode belongs to.*/
		unsafe<SceneNode> parent_node;
		/*The Model this SceneNode has.*/
		strong_handle<Model> model;

		/*The child nodes of this Node.*/
		std::vector<SceneNode> child_nodes;
		
		SceneNode(Scene &scene);
	public:
		/*The rotation of this SceneNode.*/
		math::vec3<math::Angle> rotation;
		/*The scaling of this SceneNode.*/
		math::fvec3 scaling;
		/*The position of this SceneNode.*/
		math::fvec3 position;

		SceneNode();
		SceneNode(const SceneNode &copy);
		SceneNode(SceneNode &&move);
		virtual ~SceneNode();

		SceneNode &operator=(const SceneNode &rhs);

		/*Returns the parent SceneNode of this SceneNode, if any.*/
		unsafe<SceneNode> parentNode() const;

		/*Returns whether this SceneNode is part of the given Scene.*/
		bool belongsToScene(const Scene &scene);
		
		bool isLeaf() const;
		unsafe<SceneNode> nextSibling();
		unsafe<const SceneNode> nextSibling() const;
		unsafe<SceneNode> prevSibling();
		unsafe<const SceneNode> prevSibling() const;
		unsafe<SceneNode> firstChild();
		unsafe<const SceneNode> firstChild() const;
		unsafe<SceneNode> lastChild();
		unsafe<const SceneNode> lastChild() const;

		/*Releases the direct child SceneNode child, and stores it in out_node, if out_node is set.*/
		void releaseChild(notnull<SceneNode> child, unsafe<SceneNode> out_node);

		/*Adds the given SceneNode to this SceneNode.
		Note that this copies the passed SceneNode. Because of this,
		changes made to the passed SceneNode will not affect this SceneNodes new child.
		Use the returned notnull instead to access the copy owned by this SceneNode.*/
		notnull<SceneNode> addChild(const SceneNode &node);

		void setModel(strong_handle<Model> model);
		strong_handle<Model> getModel();
		strong_handle<const Model> getModel() const;

		/*If the new parent is child or a child of child, or this SceneNode, does nothing.*/
		notnull<SceneNode> transferChild(notnull<SceneNode> child, SceneNode &new_parent);


		/*Checks whether the passed SceneNode is a child of this SceneNode or any of its children (recursively)*/
		bool isfarchild(notnull<SceneNode> child) const;

		/*This function calculates the transformation matrix of this SceneNode.
		Be sure not to call it redundantly.*/
		math::fmat4x4 getTransformation() const;
	};
}

#endif