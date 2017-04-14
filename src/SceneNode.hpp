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
	class Scene;
	/** The base scene node class used for representing entities in a scene.
	It has a tree-based layout. */
	class SceneNode
	{	friend class Scene;

		/** The Scene this SceneNode belongs to. */
		Scene * scene;
		/** The SceneNode this SceneNode belongs to. */
		SceneNode * parent_node;
		/** The Model this SceneNode has. */
		Shared<Model> model;

		/** The child nodes of this Node. */
		std::vector<SceneNode> child_nodes;

		SceneNode(Scene &scene);
	public:
		/** The rotation of this SceneNode. */
		math::Vec3<math::Angle> rotation;
		/** The scaling of this SceneNode. */
		math::fvec3_t scaling;
		/** The position of this SceneNode. */
		math::fvec3_t position;

		SceneNode();
		SceneNode(const SceneNode &copy);
		SceneNode(SceneNode &&move);
		virtual ~SceneNode();

		SceneNode &operator=(const SceneNode &rhs);
		SceneNode &operator=(SceneNode &&rhs);

		/** Returns the parent SceneNode of this SceneNode, if any. */
		SceneNode * parentNode() const;

		/** Returns whether this SceneNode is part of the given Scene. */
		bool belongsToScene(const Scene &scene);

		bool isLeaf() const;
		SceneNode * nextSibling();
		const SceneNode * nextSibling() const;
		SceneNode * prevSibling();
		const SceneNode * prevSibling() const;
		SceneNode * firstChild();
		const SceneNode * firstChild() const;
		SceneNode * lastChild();
		const SceneNode * lastChild() const;

		SceneNode * nthChild(size_t child);
		const SceneNode * nthChild(size_t child) const;
		size_t children() const;

		/** Releases the direct child SceneNode child, and stores it in out_node, if out_node is set. */
		void releaseChild(NotNull<SceneNode> child, SceneNode * out_node);

		/** Adds the given SceneNode to this SceneNode.
		Note that this copies the passed SceneNode. Because of this,
		changes made to the passed SceneNode will not affect this SceneNodes new child.
		Use the returned NotNull instead to access the copy owned by this SceneNode. */
		NotNull<SceneNode> addChild(const SceneNode &node);

		void setModel(Shared<Model> model);
		Shared<Model> getModel();
		Shared<const Model> getModel() const;

		/** If the new parent is child or a child of child, or this SceneNode, does nothing. */
		NotNull<SceneNode> transferChild(NotNull<SceneNode> child, SceneNode &new_parent);


		/** Checks whether the passed SceneNode is a child of this SceneNode or any of its children (recursively. */
		bool isfarchild(NotNull<SceneNode> child) const;

		/** This function calculates the transformation matrix of this SceneNode.
		Be sure not to call it redundantly. */
		math::fmat4x4_t getTransformation() const;
	};
}

#endif