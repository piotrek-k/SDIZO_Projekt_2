#pragma once
class ListMember
{
	int value = 0;
	ListMember* next = nullptr;
	//ListMember* prev;
	bool initialized = false;
	bool first = false;

public:
	ListMember();
	ListMember(int value);
	ListMember(ListMember * prev);
	~ListMember();

	bool IsNull();
	bool IsNotNull();
	void Build(int value);
	void AddAtTheEnd(int number);
	ListMember* getNext();

	int GetValue();
};

