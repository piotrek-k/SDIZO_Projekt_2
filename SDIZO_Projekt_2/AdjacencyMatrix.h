#pragma once
#include "Container.h"
class AdjacencyMatrix :
	public Container
{
	int numberOfNodes = 0;
	int numberOfEdges = 0;
	bool isDirected = false;
	int** matrix = NULL;

public:
	AdjacencyMatrix();
	~AdjacencyMatrix();

	void InsertNode(int initialNode, int endNode, int weight);
	void DeclareSize(int numberOfEdges, int numberOfNodes, int additionalParam);
	void Display(std::ostream& stream);
};

