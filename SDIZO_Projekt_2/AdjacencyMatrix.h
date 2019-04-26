#pragma once
#include "Container.h"
#include "MatrixMember.h"
class AdjacencyMatrix :
	public Container
{
	MatrixMember** matrix = NULL;

public:
	AdjacencyMatrix();
	AdjacencyMatrix(bool isDirected);
	~AdjacencyMatrix();

	void InsertNode(int initialNode, int endNode, int weight);
	void DeclareSize(int numberOfEdges, int numberOfNodes, int additionalParam);
	void Display(std::ostream& stream);
};

