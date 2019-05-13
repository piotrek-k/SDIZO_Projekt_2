#pragma once
#include <ostream>

class ShortestPathsContainer {
public:
	long long* minCostTable;
	int* prevStepsTable;
	int numberOfNodes;
	bool resultsCorrect = true;

	void Display(std::ostream& stream);

	// Dzia³anie algorytmu powiod³o siê. Zapisz wyniki.
	ShortestPathsContainer(long long* minCostTable, int* prevStepsTable, int numberOfNodes);

	// Utworzenie obiektu z domyœlnymi ustawieniami oznacza, ¿e algorytm najkrótszej œcie¿ki siê nie powiód³.
	ShortestPathsContainer();
};