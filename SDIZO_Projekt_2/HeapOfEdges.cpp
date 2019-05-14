//#include "stdafx.h"
#include "HeapOfEdges.h"
#include <string>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

/// <summary>
/// Zwraca numer indeksu rodzica wêz³a o podanym indeksie
/// </summary>
/// <param name="index"></param>
/// <returns></returns>
int HeapOfEdges::getIndexOfParent(int index)
{
	int x = floor((index - 1) / 2);
	return x;
}

/// <summary>
/// Zwraca numer indeksu lewego potomka wêz³a
/// </summary>
/// <param name="index"></param>
/// <returns></returns>
int HeapOfEdges::getLeftChildIndex(int index)
{
	return 2 * index + 1;
}

/// <summary>
/// Zwraca numer indeksu prawego potomka wêz³a
/// </summary>
/// <param name="index"></param>
/// <returns></returns>
int HeapOfEdges::getRightChildIndex(int index)
{
	return 2 * index + 2;
}

/// <summary>
/// przywróæ w³asnoœæ kopca
/// </summary>
void HeapOfEdges::buildHeap()
{
	for (int x = floor(this->getDeclaredSize() / 2) - 1; x >= 0; x--) {
		this->heapify(x);
	}
}

/// <summary>
/// sprawdŸ poprawnoœæ po³o¿enia wêz³a o podanym indeksie
/// </summary>
/// <param name="index"></param>
void HeapOfEdges::heapify(int index)
{
	int l = this->getLeftChildIndex(index);
	int r = this->getRightChildIndex(index);
	int smallest = 0;

	if (l < this->getDeclaredSize() && this->tab[l]->weight < this->tab[index]->weight) {
		smallest = l;
	}
	else {
		smallest = index;
	}

	if (r < this->getDeclaredSize() && this->tab[r]->weight < this->tab[smallest]->weight) {
		smallest = r;
	}

	if (smallest != index) {
		Edge* t = this->tab[index];
		this->tab[index] = this->tab[smallest];
		this->tab[smallest] = t;
		this->heapify(smallest);
	}
}

/// <summary>
/// sprawdŸ czy element jest poprawnie u³o¿ony wzglêdem parenta.
/// jeœli nie, zamieñ ich wartoœci
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
void HeapOfEdges::validateParent(int index)
{
	int indexOfParent = this->getIndexOfParent(index);
	Edge* elemValue = this->tab[index];
	Edge* parentValue = this->tab[indexOfParent];
	if (indexOfParent >= 0 && indexOfParent != index && elemValue->weight < parentValue->weight) {
		this->tab[index] = parentValue;
		this->tab[indexOfParent] = elemValue;
		validateParent(indexOfParent);
	}
}

/// <summary>
/// sprawdŸ czy wartoœæ jest w kopcu
/// </summary>
/// <param name="val"></param>
/// <returns></returns>
bool HeapOfEdges::findValue(Edge * val)
{
	return this->searchFromIndex(val, 0);
}

Edge* HeapOfEdges::getValueAtIndex(int index)
{
	if (!indexIsValid(index)) {
		return NULL;
	}
	return tab[index];
}

bool HeapOfEdges::indexIsValid(int index)
{
	if (index < 0 || index >= getDeclaredSize()) {
		return false;
	}
	return true;
}

/// <summary>
/// Funkcja pomocnicza do findValue
/// </summary>
/// <param name="val"></param>
/// <param name="index"></param>
/// <returns></returns>
bool HeapOfEdges::searchFromIndex(Edge * val, int index)
{
	if (index >= this->getDeclaredSize()) {
		return false;
	}

	if (this->tab[index] == val) {
		return true;
	}
	if (this->tab[index] < val) {
		return false;
	}

	return this->searchFromIndex(val, getLeftChildIndex(index)) || this->searchFromIndex(val, getRightChildIndex(index));
}

/// <summary>
/// Dodaje element do kopca
/// </summary>
/// <param name="key"></param>
void HeapOfEdges::addElement(Edge * key)
{
	int i = getDeclaredSize();
	this->changeDeclaredSize(i + 1);
	//tab[this->getDeclaredSize()] = key;

	while (i > 0 && this->tab[getIndexOfParent(i)]->weight > key->weight) {
		tab[i] = tab[getIndexOfParent(i)];
		i = getIndexOfParent(i);
	}

	tab[i] = key;
}

/// <summary>
/// Usuwa element o podanym indeksie z kopca
/// </summary>
/// <param name="index"></param>
void HeapOfEdges::removeElementAtIndex(int index)
{
	if (index >= getDeclaredSize()) {
		throw exception("Podany indeks jest poza zakresem tablicy");
	}
	Edge* deletedEdge = tab[index];
	tab[index] = tab[getDeclaredSize() - 1];
	tab[getDeclaredSize() - 1] = deletedEdge;
	changeDeclaredSize(getDeclaredSize() - 1);
	heapify(index);
	validateParent(index);
}

// Zapisz aktualn¹ wielkoœæ kopca. Wielkoœæ mo¿e byæ przywrócona przy u¿yciu restoreHeap()
void HeapOfEdges::setRestorePoint() {
	this->restorePoint = this->getDeclaredSize();
}

// Usuwanie wartoœci z kopca zmniejsza³o jedynie wartoœæ count
// Usuniête wci¹¿ s¹ dostêpne, wystarczy zmieniæ count na poprzedni¹ wartoœæ i zbudowaæ kopiec
void HeapOfEdges::restoreHeap() {
	this->count = this->restorePoint;
	this->buildHeap();
}

void HeapOfEdges::removeElementByValue(Edge * value)
{
	int foundIndex = -1;
	for (int a = 0; a < this->getDeclaredSize(); a++) {
		if (tab[a] == value) {
			foundIndex = a;
			break;
		}
	}

	if (foundIndex != -1) {
		this->removeElementAtIndex(foundIndex);
	}
	else {
		throw exception("Nie znaleziono podanej wartoœci");
	}
}

/// <summary>
/// Zwraca ci¹g znaków reprezentuj¹cy kopiec
/// </summary>
/// <returns></returns>
string HeapOfEdges::convertToString()
{
	string result = std::to_string(getDeclaredSize()) + ": ";
	for (int a = 0; a < getDeclaredSize(); a++) {
		result += std::to_string(tab[a]->from) + " " + std::to_string(tab[a]->to) + " (" + std::to_string(tab[a]->weight) + "); ";
	}
	return result;
}

/// <summary>
/// Zwraca tablicê odpowiadaj¹c¹ strukturze kopca
/// </summary>
/// <returns></returns>
Edge** HeapOfEdges::toArray()
{
	return tab;
}

/// <summary>
/// Przekazuje dane o kopcu na podany strumieñ
/// </summary>
/// <param name="stream"></param>
void HeapOfEdges::display(ostream & stream)
{
	stream << "Wyswietlanie kopca. Zadeklarowana wielkosc: " << getDeclaredSize() << endl;
	for (int a = 0; a < getDeclaredSize(); a++) {
		stream << tab[a] << " ";
	}
}

/// <summary>
/// Zwraca wielkoœæ kopca. Istnieje mo¿liwoœæ ¿e nie bêdzie poprawna jeœli u¿ytkownik poda b³êdny rozmiar tablicy.
/// </summary>
/// <returns></returns>
int HeapOfEdges::getDeclaredSize()
{
	return count;
}

/// <summary>
/// Zmienia wielkoœæ tablicy przechowuj¹cej kopiec na podan¹
/// </summary>
/// <param name="newCount"></param>
void HeapOfEdges::changeDeclaredSize(int newCount)
{
	if (this->count < newCount) {
		Edge** newTab = new Edge * [newCount];
		int currentSize = getDeclaredSize();
		for (int a = 0; a < min(newCount, currentSize); a++) {
			newTab[a] = this->tab[a];
		}

		clearHeap();
		this->count = newCount;
		this->tab = newTab;
	}
	else {
		this->count = newCount;
	}
}

void HeapOfEdges::clearHeap() {
	/*for (int a = 0; a < this->getDeclaredSize(); a++) {
		delete tab[a];
	}*/
	delete tab;
	tab = new Edge * [1];
	count = 0;
}

Edge* HeapOfEdges::extractFirst()
{
	Edge* first = tab[0];
	this->removeElementAtIndex(0);
	return first;
}
