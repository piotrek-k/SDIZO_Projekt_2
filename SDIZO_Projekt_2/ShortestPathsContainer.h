#pragma once
#include <ostream>

class ShortestPathsContainer {
public:
	long long* minCostTable;
	int* prevStepsTable;
	int numberOfNodes;
	bool resultsCorrect = true;

	void Display(std::ostream& stream);

	// Dzia�anie algorytmu powiod�o si�. Zapisz wyniki.
	ShortestPathsContainer(long long* minCostTable, int* prevStepsTable, int numberOfNodes);

	// Utworzenie obiektu z domy�lnymi ustawieniami oznacza, �e algorytm najkr�tszej �cie�ki si� nie powi�d�.
	ShortestPathsContainer();
};