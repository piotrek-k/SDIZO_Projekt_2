#pragma once
#include <ostream>

class DijkstraContainer {
public:
	int* minCostTable;
	int* prevStepsTable;
	int numberOfNodes;

	void Display(std::ostream& stream);

	DijkstraContainer(int* minCostTable, int* prevStepsTable, int numberOfNodes);
};