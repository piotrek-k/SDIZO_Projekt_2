#include "ListMember.h"


// Konstruktor dla warto�ci pocz�tkowych listy
ListMember::ListMember(int value)
{
	first = true;
	this->value = value;
	next = new ListMember(this);
}

// Konstruktor tworz�cy niezainicjalizowane nextValue
ListMember::ListMember(ListMember* prev)
{
	value = 0;
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

void ListMember::Build(int value)
{
	initialized = true;
	next = new ListMember(this);
	this->value = value;
}

void ListMember::AddAtTheEnd(int number)
{
	ListMember* elem = this;
	while (!elem->IsNull()) {
		elem = elem->next;
	}
	
	if (elem->IsNull) {
		elem->Build(number);
	}
}
