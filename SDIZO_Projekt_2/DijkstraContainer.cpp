#include "DijkstraContainer.h"
#include <ostream>

using namespace std;

void DijkstraContainer::Display(std::ostream& stream)
{
	stream << "minCostTable: ";
	for (int a = 0; a < this->numberOfNodes; a++) {
		stream << minCostTable[a] << " ";
	}
	stream << endl;

	stream << "prevStepsTable: ";
	for (int a = 0; a < this->numberOfNodes; a++) {
		stream << prevStepsTable[a] << " ";
	}
	stream << endl;

	// wyniki
	int* stos = new int[this->numberOfNodes];
	int stos_wsk = 0;
	for (int a = 0; a < this->numberOfNodes; a++) {
		stream << a << ": ";

		for (int j = a; j > -1; j = prevStepsTable[j]) {
			stos[stos_wsk++] = j;
		}
		while (stos_wsk) stream << stos[--stos_wsk] << " ";
		stream << "$" << minCostTable[a] << endl;
	}
}

DijkstraContainer::DijkstraContainer(int* minCostTable, int* prevStepsTable, int numberOfNodes)
{
	this->minCostTable = minCostTable;
	this->prevStepsTable = prevStepsTable;
	this->numberOfNodes = numberOfNodes;
}
