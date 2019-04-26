#include "AdjacencyMatrix.h"
#include <iostream>

using namespace std;

AdjacencyMatrix::AdjacencyMatrix()
{
}


AdjacencyMatrix::~AdjacencyMatrix()
{
}

void AdjacencyMatrix::InsertNode(int initialNode, int endNode, int weight)
{
	matrix[initialNode][endNode] = 1;
	if (!isDirected) {
		matrix[endNode][initialNode] = 1;
	}
}

void AdjacencyMatrix::DeclareSize(int numberOfEdges, int numberOfNodes, int additionalParam)
{
	//wype�nienie macierzy zerami

	matrix = new int* [numberOfNodes];
	for (int i = 0; i < numberOfNodes; i++) {
		this->matrix[i] = new int [numberOfNodes];
		for (int j = 0; j < numberOfNodes; j++) {
			this->matrix[i][j] = 0;
		}
	}

	this->numberOfEdges = numberOfEdges;
	this->numberOfNodes = numberOfNodes;
}

void AdjacencyMatrix::Display(std::ostream& stream)
{
	stream << "Wyswietlanie macierzy sasiedztwa: " << endl;
	for (int i = 0; i < numberOfNodes; i++) {
		for (int j = 0; j < numberOfNodes; j++) {
			stream << this->matrix[i][j] << "\t";
		}
		stream << endl;
	}
}
