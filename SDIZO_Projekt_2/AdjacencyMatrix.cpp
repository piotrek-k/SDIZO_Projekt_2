#include "AdjacencyMatrix.h"
#include <iostream>

using namespace std;

AdjacencyMatrix::AdjacencyMatrix(const std::string& fileName, bool isDirected)
{
	this->loadFromFile(fileName, isDirected);
	generateNodeStorage();
}

AdjacencyMatrix::AdjacencyMatrix(int numberOfEdges, int numberOfNodes, int additionalParam, bool isDirected)
{
	this->declareSize(numberOfEdges, numberOfNodes, additionalParam);
	this->isDirected = isDirected;
	generateNodeStorage();
}

AdjacencyMatrix::~AdjacencyMatrix()
{
}

void AdjacencyMatrix::InsertNode(int initialNode, int endNode, int weight)
{
	matrix[initialNode][endNode].connection = true;
	matrix[initialNode][endNode].weight = weight;
	matrix[initialNode][endNode].initialized = true;
	if (!isDirected) {
		matrix[endNode][initialNode].connection = 1;
		matrix[endNode][initialNode].weight = weight;
		matrix[endNode][initialNode].initialized = true;
	}
}

void AdjacencyMatrix::declareSize(int numberOfEdges, int numberOfNodes, int additionalParam)
{
	// wywo³anie metody z klasy bazowej
	Container::declareSize(numberOfEdges, numberOfNodes, additionalParam);

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

Node* AdjacencyMatrix::LowestCostNeighbour(int index, bool canBeDisabled)
{
	MatrixMember* row = matrix[index];
	Node* lowestCostElem = NULL;

	for (int a = 0; a < GetNumberOfNodes(); a++) {
		MatrixMember* elem = &row[a];
		if (canBeDisabled || !this->GetNode(a)->isActive()) {
			if (lowestCostElem == NULL || (elem->getWeight() < lowestCostElem->getWeight() && elem->connection)) {
				lowestCostElem = (Node*)elem;
				if (lowestCostElem->index != a) {
					lowestCostElem->index = a;
				}
			}
		}
	}

	if (lowestCostElem == NULL) {
		return new Node(EMPTY);
	}

	if (!canBeDisabled && this->GetNode(lowestCostElem->getIndex())->isActive() == true) {
		return new Node(EMPTY);
	}

	return lowestCostElem;
}

ListMember* AdjacencyMatrix::GetAllNeighbours(int nodeId)
{
	ListMember* lm = NULL;
	for (int a = 0; a < this->GetNumberOfNodes(); a++) {
		if (matrix[nodeId][a].connection) {
			if (lm == NULL) {
				lm = new ListMember(a, matrix[nodeId][a].weight);
			}
			else {
				lm->AddAtTheEnd(a, matrix[nodeId][a].weight);
			}
		}
	}
	return lm;
}

Container* AdjacencyMatrix::GenerateEmptyClone()
{
	return new AdjacencyMatrix(this->GetNumberOfEdges(), this->GetNumberOfNodes(), this->GetAdditionalParam(), this->isDirected);
}
