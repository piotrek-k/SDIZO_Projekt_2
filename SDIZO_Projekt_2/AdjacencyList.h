#pragma once
#include "Container.h"
#include "ListMember.h"
class AdjacencyList :
	public Container
{
	ListMember** lists = NULL;

public:
	AdjacencyList();
	AdjacencyList(bool isDirected);
	~AdjacencyList();

	void InsertNode(int initialNode, int endNode, int weight);
	void DeclareSize(int numberOfEdges, int numberOfNodes, int additionalParam);
	void Display(std::ostream& stream);
};

