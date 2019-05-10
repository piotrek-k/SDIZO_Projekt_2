#include "Node.h"

Node::Node() {
	this->index = 0;
	this->weight = 0;
	this->active = false;
	this->initialized = false;
}

Node::Node(NodeType type)
{
	Node::Node();
	this->initialized = (type != EMPTY);
}

Node::Node(int index, int weight)
{
	this->index = index;
	this->weight = weight;
	this->active = false;
	// Node ma jakieœ dane, wiêc mo¿na go uznaæ za zainicjowanego
	this->initialized = true;
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

bool Node::IsNull()
{
	return initialized == false;
}

bool Node::IsNotNull()
{
	return initialized == true;
}