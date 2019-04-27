#include "ListMember.h"

// Niezainicjalizowany element, bêd¹cy pocz¹tkiem listy
ListMember::ListMember()
{
	index = 0;
}

// Zainicjalizowany element, bêd¹cy pocz¹tkiem listy
ListMember::ListMember(int index, int weight)
{
	first = true;
	this->Build(index, weight);
}

// Niezainicjalizowany element, bêd¹cy kontynuacj¹ listy
ListMember::ListMember(ListMember* prev)
{
	index = 0;
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

void ListMember::Build(int index, int weight)
{
	initialized = true;
	next = new ListMember(this);
	this->index = index;
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

bool ListMember::isActive()
{
	return active == true;
}

int ListMember::getWeight()
{
	return weight;
}
