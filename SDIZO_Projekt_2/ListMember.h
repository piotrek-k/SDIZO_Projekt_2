#pragma once
class ListMember
{
	int key = 0; // id of connected node
	int weight = 0;

	ListMember* next = nullptr;
	//ListMember* prev;
	bool initialized = false;
	bool first = false;

public:
	ListMember();
	ListMember(int key, int weight);
	ListMember(ListMember * prev);
	~ListMember();

	bool IsNull();
	bool IsNotNull();
	void Build(int key,int weight);
	void AddAtTheEnd(int number, int weight);
	ListMember* getNext();

	int GetValue();
};

