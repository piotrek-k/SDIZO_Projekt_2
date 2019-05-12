#include "SDIZO_Projekt_2.h"
#include "timeCounter.h"
#include <iostream>

enum ALGORITHM_TYPE {
	PRIM,
	DIJKSTRA
};


void RunMeasurement(std::ostream& stream1, std::ostream& stream2, int numberOfNodes, int density, int howManyTimes, ALGORITHM_TYPE type) {
	// Generuj now¹, losow¹ instancjê
	AdjacencyList* al;
	AdjacencyMatrix* am;
	bool directed = false;
	TimeCounter* adjMatrixCounter = new TimeCounter();
	TimeCounter* adjListCounter = new TimeCounter();

	switch (type) {
	case DIJKSTRA:
		directed = true;
		break;
	}

	adjMatrixCounter->ResetCounter();
	adjListCounter->ResetCounter();
	for (int a = 0; a < howManyTimes; a++) {
		generateRandomGraph(numberOfNodes, density, al, am, directed);

		switch (type) {
		case DIJKSTRA:
			adjMatrixCounter->StartNextMeasurement();
			am->RunDijkstra(stream1, 0);
			adjMatrixCounter->EndSingleMeasurement();

			adjListCounter->StartNextMeasurement();
			al->RunDijkstra(stream1, 0);
			adjListCounter->EndSingleMeasurement();

			break;
		}
	}

	stream1 << numberOfNodes << "\t" << density << "\t" << howManyTimes << "\t" << adjListCounter->Summarize() << std::endl;
	stream2 << numberOfNodes << "\t" << density << "\t" << howManyTimes << "\t" << adjListCounter->Summarize() << std::endl;

}