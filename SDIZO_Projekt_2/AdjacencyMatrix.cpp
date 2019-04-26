#include "AdjacencyMatrix.h"
#include <iostream>

using namespace std;

AdjacencyMatrix::AdjacencyMatrix()
{
}

AdjacencyMatrix::AdjacencyMatrix(bool isDirected) :Container(isDirected)
{
}


AdjacencyMatrix::~AdjacencyMatrix()
{
}

void AdjacencyMatrix::InsertNode(int initialNode, int endNode, int weight)
{
	matrix[initialNode][endNode].connection = true;
	matrix[initialNode][endNode].weight = weight;
	if (!isDirected) {
		matrix[endNode][initialNode].connection = 1;
		matrix[endNode][initialNode].weight = weight;
	}
}

void AdjacencyMatrix::DeclareSize(int numberOfEdges, int numberOfNodes, int additionalParam)
{
	// wywo³anie metody z klasy bazowej
	Container::DeclareSize(numberOfEdges, numberOfNodes, additionalParam);

	//wype³nienie macierzy zerami

	matrix = new MatrixMember* [numberOfNodes];
	for (int i = 0; i < numberOfNodes; i++) {
		this->matrix[i] = new MatrixMember[numberOfNodes];
		for (int j = 0; j < numberOfNodes; j++) {
			this->matrix[i][j].connection = 0;
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
			stream << this->matrix[i][j].connection << "(" << this->matrix[i][j].weight << ")" << "\t";
		}
		stream << endl;
	}
}
