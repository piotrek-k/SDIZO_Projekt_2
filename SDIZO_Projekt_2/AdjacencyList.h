#pragma once
#include "Container.h"
#include "ListMember.h"
#include "Node.h"
class AdjacencyList :
	public Container
{
	ListMember** lists = NULL;
	//ListMember** algorithmResult = NULL;

	// PRIM
	ListMember* alreadyUsedNodes = NULL;

public:
	AdjacencyList(const std::string& fileName, bool isDirected);
	AdjacencyList(int numberOfEdges, int numberOfNodes, int additionalParam, bool isDirected);
	~AdjacencyList();

	void InsertNode(int initialNode, int endNode, int weight);
	void declareSize(int numberOfEdges, int numberOfNodes, int additionalParam);
	void Display(std::ostream& stream);
	Container* GenerateEmptyClone();

	
	Node* GetNode(int index);

	// szuka minimalnego wierzchołka grafu
	Node* LowestCostNeighbour(int index, bool canBeDisabled);
};

