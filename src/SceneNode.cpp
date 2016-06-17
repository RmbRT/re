#include "SceneNode.hpp"
#include "Scene.hpp"

namespace re
{

	math::fmat4x4 SceneNode::getTransformation() const
	{
		return math::fmat4x4::transformation(position, rotation, scaling);
	}

	SceneNode::~SceneNode() {}
	SceneNode::SceneNode(): parent_node(nullptr), scene(nullptr), rotation(), position(), scaling(1,1,1), model(nullptr) { }
	SceneNode::SceneNode(SceneNode &&move): parent_node(move.parent_node), child_nodes(std::move(move.child_nodes)), scene(move.scene), rotation(move.rotation), position(move.position), scaling(move.scaling), model(move.model)  {
		for(SceneNode &node: child_nodes)
			node.parent_node = this;
	}
	SceneNode::SceneNode(const SceneNode &copy): parent_node(copy.parent_node), child_nodes(copy.child_nodes), scene(copy.scene), rotation(copy.rotation), position(copy.position), scaling(copy.scaling), model(copy.model)
	{
		for(SceneNode &node: child_nodes)
			node.parent_node = this;
	}
	SceneNode::SceneNode(Scene &scene) : parent_node(nullptr), scene(scene), rotation(), position(), scaling(1,1,1), model(nullptr)  { }


	SceneNode &SceneNode::operator=(const SceneNode &rhs)
	{
		if(&rhs == this)
			return *this;
		parent_node = rhs.parent_node;
		child_nodes = rhs.child_nodes;

		rotation = rhs.rotation;
		position = rhs.position;
		scaling = rhs.scaling;
		model = rhs.model;

		for(SceneNode &child: child_nodes)
			child.parent_node = this;
		
		return *this;
	}

	SceneNode &SceneNode::operator=(SceneNode &&rhs)
	{
		if(&rhs == this)
			return *this;
		parent_node = rhs.parent_node;
		child_nodes = std::move(rhs.child_nodes);

		rotation = rhs.rotation;
		position = rhs.position;
		scaling = rhs.scaling;
		model = rhs.model;

		for(SceneNode &child: child_nodes)
			child.parent_node = this;

		return *this;
	}

	void SceneNode::releaseChild(NotNull<SceneNode> node, SceneNode * out_node)
	{
		RE_ASSERT(node>= &child_nodes.front() && node<=&child_nodes.back() && node->parent_node == this);
		
		if(out_node)
			*out_node = node;

		size_t i = node-&child_nodes.front();
		child_nodes.erase(child_nodes.begin()+i);
	}

	SceneNode * SceneNode::parentNode() const
	{
		return parent_node;
	}

	bool SceneNode::belongsToScene(const Scene &scene)
	{
		return this->scene == &scene;
	}

	bool SceneNode::isLeaf() const
	{
		return child_nodes.empty();
	}

	SceneNode * SceneNode::nextSibling()
	{
		if(!parent_node)
			return nullptr;

		unsigned index = this-&parent_node->child_nodes.front();
		if(index+1<parent_node->child_nodes.size())
			return parent_node->child_nodes[index+1];
		else
			return nullptr;
	}
	const SceneNode * SceneNode::nextSibling() const
	{
		if(!parent_node)
			return nullptr;

		unsigned index = this-&parent_node->child_nodes.front();
		if(index+1<parent_node->child_nodes.size())
			return parent_node->child_nodes[index+1];
		else
			return nullptr;
	}
	SceneNode * SceneNode::prevSibling()
	{
		if(!parent_node)
			return nullptr;
		unsigned index = this-&parent_node->child_nodes.front();
		if(index>0)
			return parent_node->child_nodes[index-1];
		else return nullptr;
	}
	const SceneNode * SceneNode::prevSibling() const
	{
		if(!parent_node)
			return nullptr;
		unsigned index = this-&parent_node->child_nodes.front();
		if(index>0)
			return parent_node->child_nodes[index-1];
		else return nullptr;
	}
	SceneNode * SceneNode::firstChild()
	{
		return child_nodes.size() ? &child_nodes.front() : nullptr;
	}
	const SceneNode * SceneNode::firstChild() const
	{
		return child_nodes.size() ? &child_nodes.front() : nullptr;
	}
	SceneNode * SceneNode::lastChild()
	{
		return child_nodes.size() ? &child_nodes.back() : nullptr;
	}
	const SceneNode * SceneNode::lastChild() const
	{
		return child_nodes.size() ? &child_nodes.back() : nullptr;
	}

	SceneNode * SceneNode::nthChild(size_t child)
	{
		return child_nodes.size() > child ? &child_nodes[child] : nullptr;
	}
	const SceneNode * SceneNode::nthChild(size_t child) const
	{
		return child_nodes.size() > child ? &child_nodes[child] : nullptr;
	}

	size_t SceneNode::children() const { return child_nodes.size(); }

	NotNull<SceneNode> SceneNode::addChild(const SceneNode &node)
	{
		RE_ASSERT(!node.parent_node);

		child_nodes.push_back(node);
		SceneNode &handle = child_nodes.back();
		handle.parent_node = this;
		handle.scene = scene;
		return handle;
	}
	void SceneNode::setModel(strong_handle<Model> model)
	{
		this->model = model;
	}
	strong_handle<Model> SceneNode::getModel()
	{
		return model;
	}
	strong_handle<const Model> SceneNode::getModel() const
	{
		return reinterpret_cast<const strong_handle<const Model>&>(model);
	}

	bool SceneNode::isfarchild(NotNull<SceneNode> child) const
	{
		for(const SceneNode &_child: child_nodes)
			if(&_child == child)
				return true;
			else if(_child.isfarchild(child))
				return true;
			else
				continue;

		return false;
	}

	NotNull<SceneNode> SceneNode::transferChild(NotNull<SceneNode> child, SceneNode &newParent)
	{
		if(this == &newParent)
			return child;

		RE_ASSERT(child != newParent && !child->isfarchild(newParent));

		SceneNode temp;

		releaseChild(child, &temp);
		return newParent.addChild(temp);
	}
}