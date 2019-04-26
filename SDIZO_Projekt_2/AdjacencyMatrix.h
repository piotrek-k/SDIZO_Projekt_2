#pragma once
#include "Container.h"
class AdjacencyMatrix :
	public Container
{
	int** matrix = NULL;

public:
	AdjacencyMatrix();
	AdjacencyMatrix(bool isDirected);
	~AdjacencyMatrix();

	void InsertNode(int initialNode, int endNode, int weight);
	void DeclareSize(int numberOfEdges, int numberOfNodes, int additionalParam);
	void Display(std::ostream& stream);
};

