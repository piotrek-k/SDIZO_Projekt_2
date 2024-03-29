#include "AdjacencyList.h"

#include <iostream>

AdjacencyList::AdjacencyList()
{
}

AdjacencyList::AdjacencyList(const std::string& fileName, bool isDirected) {
	this->loadFromFile(fileName, isDirected);
	this->isDirected = isDirected;
	generateNodeStorage();
}

AdjacencyList::AdjacencyList(int numberOfEdges, int numberOfNodes, int additionalParam, bool isDirected)
{
	this->declareSize(numberOfEdges, numberOfNodes, additionalParam);
	this->isDirected = isDirected;
	generateNodeStorage();
}


AdjacencyList::~AdjacencyList()
{
	this->Clean();
}

void AdjacencyList::InsertEdge(int initialNode, int endNode, int weight, bool enableEdgesHeap)
{
	lists[initialNode]->AddAtTheEnd(endNode, weight);

	//KRUSKAL 
	if (enableEdgesHeap) {
		edgesHeap->addElement(new Edge(initialNode, endNode, weight));
	}
	//this->lastEdgeKey++;

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

Node* AdjacencyList::LowestCostNeighbour(int index, bool canBeDisabled)
{
	ListMember* elem = lists[index];
	Node* lowestCostElem = NULL;

	while (elem->IsNotNull()) {
		if (canBeDisabled || !this->GetNode(elem->getIndex())->isActive()) {
			if (lowestCostElem == NULL || elem->getWeight() < lowestCostElem->getWeight()) {
				lowestCostElem = (Node*)elem;
			}
		}

		elem = elem->getNext();
	}

	if (lowestCostElem == NULL) {
		return new Node(EMPTY);
	}

	if (!canBeDisabled && this->GetNode(lowestCostElem->getIndex())->isActive() == true) {
		return new Node(EMPTY);
	}

	return lowestCostElem;
}

ListMember* AdjacencyList::GetAllNeighbours(int nodeId)
{
	return lists[nodeId];
}

void AdjacencyList::Clean()
{
	// usuwanie imformacji o wierzchołkach
	for (int a = 0; a < numberOfNodes; a++) {
		delete stateOfNodes[a];
	}

	// usunięcie danych o połączeniach wierzchołków
	for (int l = 0; l < numberOfNodes; l++) {
		delete lists[l];
	}

	// TODO: usunięcie alreadyUsedNodes?

	numberOfNodes = 0;
	numberOfEdges = 0;
	additionalParam = 0;
}

bool AdjacencyList::DoesConnectionExist(int node1, int node2)
{
	ListMember* elem = lists[node1];
	while (elem->IsNotNull()) {

		if (elem->getIndex() == node2) {
			return true;
		}

		elem = elem->getNext();
	}
	return false;
}
