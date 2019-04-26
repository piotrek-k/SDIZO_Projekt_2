#include "AdjacencyList.h"

#include <iostream>

AdjacencyList::AdjacencyList()
{
}

AdjacencyList::AdjacencyList(bool isDirected):Container(isDirected)
{
}


AdjacencyList::~AdjacencyList()
{
}

void AdjacencyList::InsertNode(int initialNode, int endNode, int weight)
{
	lists[initialNode]->AddAtTheEnd(endNode);

	if (!this->isDirected) {
		lists[endNode]->AddAtTheEnd(initialNode);
	}
}

void AdjacencyList::DeclareSize(int numberOfEdges, int numberOfNodes, int additionalParam)
{
	Container::DeclareSize(numberOfEdges, numberOfNodes, additionalParam);

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
			stream << elem->GetValue() << " ";
			elem = elem->getNext();
		}

		stream << std::endl;
	}
}
