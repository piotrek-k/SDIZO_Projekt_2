#include<string>
#include "Edge.h"
using namespace std;
#pragma once
class HeapOfEdges
{
	Edge** tab;
	int count = 0; //zadeklarowana w pliku iloœæ elementów w tablicy
	int restorePoint = 0; // wielkoœæ kopca do której zamierzamy powróciæ

	bool searchFromIndex(Edge* val, int index); //funkcja pomocnicza do findValue

public:

	int getIndexOfParent(int index);
	int getLeftChildIndex(int index);
	int getRightChildIndex(int index);

	void buildHeap();
	void heapify(int index);
	void validateParent(int index);

	void addElement(Edge* key);
	void removeElementAtIndex(int index);
	void setRestorePoint();
	void restoreHeap();
	void removeElementByValue(Edge* value);

	bool findValue(Edge* val);
	Edge* getValueAtIndex(int index);
	bool indexIsValid(int index);
	
	std::string convertToString();
	Edge** toArray();
	void display(ostream & stream);

	int getDeclaredSize();
	void changeDeclaredSize(int newCount);

	void clearHeap();

	Edge* extractFirst();
};

