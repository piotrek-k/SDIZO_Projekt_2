#pragma once
#include "Container.h"
#include "MatrixMember.h"
#include "ListMember.h"
class AdjacencyMatrix :
	public Container
{
	MatrixMember** matrix = NULL;
	
public:
	AdjacencyMatrix();
	AdjacencyMatrix(const std::string& fileName, bool isDirected);
	AdjacencyMatrix(int numberOfEdges, int numberOfNodes, int additionalParam, bool isDirected);
	~AdjacencyMatrix();

	void InsertEdge(int initialNode, int endNode, int weight, bool enableEdgesHeap = true);
	void declareSize(int numberOfEdges, int numberOfNodes, int additionalParam);
	void Display(std::ostream& stream);

	Node* LowestCostNeighbour(int index, bool canBeDisabled);
	ListMember* GetAllNeighbours(int nodeId);

	Container* GenerateEmptyClone();

	void Clean();

	bool DoesConnectionExist(int node1, int node2);
};

