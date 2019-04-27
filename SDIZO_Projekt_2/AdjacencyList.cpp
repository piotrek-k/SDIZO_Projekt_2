#include "AdjacencyList.h"

#include <iostream>

AdjacencyList::AdjacencyList(const std::string& fileName, bool isDirected) : Container(fileName, isDirected)
{
	this->loadFromFile(fileName, isDirected);
}

AdjacencyList::AdjacencyList(int numberOfEdges, int numberOfNodes, int additionalParam, bool isDirected) :Container(numberOfEdges, numberOfNodes, additionalParam, isDirected)
{
	this->declareSize(numberOfEdges, numberOfNodes, additionalParam);
	this->isDirected = isDirected;
}


AdjacencyList::~AdjacencyList()
{
}

void AdjacencyList::InsertNode(int initialNode, int endNode, int weight)
{
	lists[initialNode]->AddAtTheEnd(endNode, weight);

	if (!this->isDirected) {
		lists[endNode]->AddAtTheEnd(initialNode, weight);
	}
}

void AdjacencyList::declareSize(int numberOfEdges, int numberOfNodes, int additionalParam)
{
	Container::declareSize(numberOfEdges, numberOfNodes, additionalParam);

	lists = new ListMember * [numberOfNodes];
	for (int l = 0; l < numberOfNodes; l++) {
		lists[l] = new ListMember();
	}
}

void AdjacencyList::Display(std::ostream& stream)
{
	for (int a = 0; a < numberOfNodes; a++) {
		stream << "[" << a << "] :";

		ListMember* elem = lists[a];
		while (elem->IsNotNull()) {
			stream << elem->getIndex() << " (" << elem->getWeight() << ") ";
			elem = elem->getNext();
		}

		stream << std::endl;
	}
}

Container* AdjacencyList::GenerateEmptyClone()
{
	return new AdjacencyList(this->GetNumberOfEdges(), this->GetNumberOfNodes(), this->GetAdditionalParam(), this->isDirected);
}

Node* AdjacencyList::GetNode(int index)
{
	return (Node*)lists[index];
}

Node* AdjacencyList::LowestCostNeighbour(int index, bool canBeDisabled)
{
	ListMember* elem = lists[index];
	//int lowestCost = elem->getWeight();
	Node* lowestCostElem = NULL;
	//int lowestCostElemIndex = elem->GetKey();

	while (elem->IsNotNull()) {
		if (canBeDisabled || !this->GetNode(elem->getIndex())->isActive()) {
			if (lowestCostElem == NULL || elem->getWeight() < lowestCostElem->getWeight()) {
				lowestCostElem = (Node*)elem;
			}
		}
		
		elem = elem->getNext();
	}

	if (lowestCostElem == NULL) {
		return new Node(-1, -1);
	}

	if (!canBeDisabled && this->GetNode(lowestCostElem->getIndex())->isActive() == true) {
		return new Node(-1, -1);
	}

	return lowestCostElem;
}
