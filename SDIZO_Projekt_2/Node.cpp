#include "Node.h"

Node::Node() {
	this->index = 0;
	this->weight = 0;
	this->active = false;
}

Node::Node(NodeType type)
{
	Node::Node();
	this->nullNode = (type == EMPTY);
}

Node::Node(int index, int weight)
{
	this->index = index;
	this->weight = weight;
	this->active = false;
}

Node::~Node()
{
}

bool Node::isActive()
{
	return active == true;
}

void Node::setActiveState(bool active)
{
	this->active = active;
}

int Node::getWeight()
{
	return weight;
}

int Node::getIndex()
{
	return index;
}

bool Node::isNull()
{
	return nullNode == true;
}

bool Node::isNotNull()
{
	return nullNode == false;
}
