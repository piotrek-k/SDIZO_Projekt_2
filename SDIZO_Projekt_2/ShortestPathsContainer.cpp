#include <ostream>
#include "ShortestPathsContainer.h"

using namespace std;

void ShortestPathsContainer::Display(std::ostream& stream)
{
	if (this->resultsCorrect) {
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
	else {
		stream << "Algorytm zwrocil wartosc FALSE";
	}
}

ShortestPathsContainer::ShortestPathsContainer(long long* minCostTable, int* prevStepsTable, int numberOfNodes)
{
	this->resultsCorrect = true;
	this->minCostTable = minCostTable;
	this->prevStepsTable = prevStepsTable;
	this->numberOfNodes = numberOfNodes;
}

ShortestPathsContainer::ShortestPathsContainer()
{
	resultsCorrect = false;
}
