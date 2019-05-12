#pragma once
#include "Container.h"
#include "MatrixMember.h"
#include "ListMember.h"
class AdjacencyMatrix :
	public Container
{
	MatrixMember** matrix = NULL;
	
public:
	AdjacencyMatrix(const std::string& fileName, bool isDirected);
	AdjacencyMatrix(int numberOfEdges, int numberOfNodes, int additionalParam, bool isDirected);
	~AdjacencyMatrix();

	void InsertNode(int initialNode, int endNode, int weight);
	void declareSize(int numberOfEdges, int numberOfNodes, int additionalParam);
	void Display(std::ostream& stream);

	Node* LowestCostNeighbour(int index, bool canBeDisabled);
	ListMember* GetAllNeighbours(int nodeId);

	Container* GenerateEmptyClone();

	void Clean();
};

