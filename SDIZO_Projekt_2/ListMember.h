#pragma once
#include "Node.h"

class ListMember : public Node
{
	ListMember* next = nullptr;
	bool first = false; // TODO: potrzebne?

public:
	ListMember();
	ListMember(int index, int weight);
	ListMember(ListMember * prev);
	~ListMember();

	void Build(int index,int weight);
	void AddAtTheEnd(int number, int weight);
	ListMember* getNext();
};

