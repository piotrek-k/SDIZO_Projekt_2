#include "ListMember.h"

// Niezainicjalizowany element, bêd¹cy pocz¹tkiem listy
ListMember::ListMember()
{
	key = 0;
}

// Zainicjalizowany element, bêd¹cy pocz¹tkiem listy
ListMember::ListMember(int key, int weight)
{
	first = true;
	this->Build(key, weight);
}

// Niezainicjalizowany element, bêd¹cy kontynuacj¹ listy
ListMember::ListMember(ListMember* prev)
{
	key = 0;
	if (!prev->IsNull()) {
		next = new ListMember(this);
	}
}

ListMember::~ListMember()
{
}

bool ListMember::IsNull()
{
	return initialized == false;
}

bool ListMember::IsNotNull()
{
	return initialized == true;
}

void ListMember::Build(int key, int weight)
{
	initialized = true;
	next = new ListMember(this);
	this->key = key;
	this->weight = weight;
}

void ListMember::AddAtTheEnd(int number, int weight)
{
	ListMember* elem = this;
	while (elem->IsNotNull()) {
		elem = elem->next;
	}
	
	if (elem->IsNull()) {
		elem->Build(number, weight);
	}
}

ListMember* ListMember::getNext()
{
	return this->next;
}

int ListMember::GetValue()
{
	return key;
}
