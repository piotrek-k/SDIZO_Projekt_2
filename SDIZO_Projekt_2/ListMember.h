#pragma once
#include "Node.h"

class ListMember : public Node
{
	ListMember* next = nullptr;
	bool initialized = false;
	bool first = false; // TODO: potrzebne?

public:
	ListMember();
	ListMember(int index, int weight);
	ListMember(ListMember * prev);
	~ListMember();

	bool IsNull();
	bool IsNotNull();
	void Build(int index,int weight);
	void AddAtTheEnd(int number, int weight);
	ListMember* getNext();
};

