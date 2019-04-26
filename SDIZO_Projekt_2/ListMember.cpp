#include "ListMember.h"

// Niezainicjalizowany element, b�d�cy pocz�tkiem listy
ListMember::ListMember()
{
	value = 0;
}

// Zainicjalizowany element, b�d�cy pocz�tkiem listy
ListMember::ListMember(int value)
{
	first = true;
	this->Build(value);
}

// Niezainicjalizowany element, b�d�cy kontynuacj� listy
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
	while (elem->IsNotNull()) {
		elem = elem->next;
	}
	
	if (elem->IsNull()) {
		elem->Build(number);
	}
}

ListMember* ListMember::getNext()
{
	return this->next;
}

int ListMember::GetValue()
{
	return value;
}
