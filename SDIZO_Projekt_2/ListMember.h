#pragma once
class ListMember
{
	int value;
	ListMember* next;
	ListMember* prev;
	bool initialized = false;
	bool first = false;

public:
	ListMember(int value);
	ListMember(ListMember * prev);
	~ListMember();

	bool IsNull();
	bool IsNotNull();
	void Build(int value);
	void AddAtTheEnd(int number);
};

