#include "Node.h"

Node::Node() {
	this->index = 0;
	this->weight = 0;
	this->active = false;
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

int Node::getWeight()
{
	return weight;
}

int Node::getIndex()
{
	return index;
}
