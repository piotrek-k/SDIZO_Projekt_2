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
	AdjacencyList();
	AdjacencyList(const std::string& fileName, bool isDirected);
	AdjacencyList(int numberOfEdges, int numberOfNodes, int additionalParam, bool isDirected);
	~AdjacencyList();

	void InsertEdge(int initialNode, int endNode, int weight, bool enableEdgesHeap = true);
	void declareSize(int numberOfEdges, int numberOfNodes, int additionalParam);
	void Display(std::ostream& stream);
	Container* GenerateEmptyClone();


	// szuka minimalnego wierzcho³ka grafu
	Node* LowestCostNeighbour(int index, bool canBeDisabled);
	
	// zwraca s¹siaduj¹ce wierzcho³ki
	ListMember* GetAllNeighbours(int nodeId);

	void Clean();

	bool DoesConnectionExist(int node1, int node2);
};

