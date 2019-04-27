#pragma once
#include "Node.h"

class ListMember : public Node
{
	//int index = 0; // id of connected node
	//int weight = 0;

	//bool active = true;

	ListMember* next = nullptr;
	//ListMember* prev;
	bool initialized = false;
	bool first = false;

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

	bool isActive();
	int getWeight();
};

