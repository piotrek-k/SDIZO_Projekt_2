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


	// szuka minimalnego wierzcho³ka grafu
	Node* LowestCostNeighbour(int index, bool canBeDisabled);
	
	// zwraca s¹siaduj¹ce wierzcho³ki
	ListMember* GetAllNeighbours(int nodeId);
};

