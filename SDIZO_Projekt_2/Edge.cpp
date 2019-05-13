#include "Edge.h"



Edge::Edge(int from, int to, int weight)
{
	this->from = from;
	this->to = to;
	this->weight = weight;
}

Edge::~Edge()
{
}
