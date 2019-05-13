#include "SDIZO_Projekt_2.h"
#include "timeCounter.h"
#include <iostream>
#include <fstream>

using namespace std;

enum ALGORITHM_TYPE {
	PRIM,
	DIJKSTRA,
	BELLMANFORD
};


void RunMeasurement(std::ostream& stream1, std::ostream& stream2, int numberOfNodes, int density, int howManyTimes, ALGORITHM_TYPE type) {
	// Generuj now¹, losow¹ instancjê
	AdjacencyList* al = NULL;
	AdjacencyMatrix* am = NULL;
	AdjacencyList* output_al = NULL;
	AdjacencyMatrix* output_am = NULL;
	bool directed = false;
	TimeCounter* adjMatrixCounter = new TimeCounter();
	TimeCounter* adjListCounter = new TimeCounter();

	switch (type) {
	case DIJKSTRA:
		directed = true;
		break;
	case PRIM:
		directed = false;
		break;
	}

	adjMatrixCounter->ResetCounter();
	adjListCounter->ResetCounter();
	for (int a = 0; a < howManyTimes; a++) {
		generateRandomGraph(numberOfNodes, density, al, am, directed);

		switch (type) {
		case PRIM:
			output_al = (AdjacencyList*)al->GenerateEmptyClone();
			adjListCounter->StartNextMeasurement();
			al->RunPrimSaveElsewhere(0, output_al);
			adjListCounter->EndSingleMeasurement();
			delete output_al;

			output_am = (AdjacencyMatrix*)am->GenerateEmptyClone();
			adjMatrixCounter->StartNextMeasurement();
			am->RunPrimSaveElsewhere(0, output_am);
			adjMatrixCounter->EndSingleMeasurement();
			delete output_am;

		case DIJKSTRA:
			adjMatrixCounter->StartNextMeasurement();
			am->RunDijkstra(0);
			adjMatrixCounter->EndSingleMeasurement();

			adjListCounter->StartNextMeasurement();
			al->RunDijkstra(0);
			adjListCounter->EndSingleMeasurement();

			break;

		case BELLMANFORD:
			adjMatrixCounter->StartNextMeasurement();
			am->RunBellmanFord(0);
			adjMatrixCounter->EndSingleMeasurement();

			adjListCounter->StartNextMeasurement();
			al->RunBellmanFord(0);
			adjListCounter->EndSingleMeasurement();
			break;
		}
	}

	stream1 << numberOfNodes << "\t" << density << "\t" << howManyTimes << "\t" << adjListCounter->Summarize() << std::endl;
	stream2 << numberOfNodes << "\t" << density << "\t" << howManyTimes << "\t" << adjMatrixCounter->Summarize() << std::endl;

	delete al;
	delete am;
}

void RunAllMeasurements() {
	int nodes_to_research[] = { 10, 100, 200 };
	const int nodes_to_research_size = 3;
	int densities_to_research[] = { 25, 50, 75, 99 };
	const int densities_to_research_size = 4;

	{
		ofstream dijkstra_list;
		dijkstra_list.open("results_dijkstra_list.txt");

		ofstream dijkstra_matrix;
		dijkstra_matrix.open("results_dijkstra_matrix.txt");

		for (int n = 0; n < nodes_to_research_size; n++) {
			for (int d = 0; d < densities_to_research_size; d++) {
				cout << "Dijkstra N: " << n << " D: " << d << endl;

				if (dijkstra_list && dijkstra_matrix) {
					RunMeasurement(dijkstra_list, dijkstra_matrix, nodes_to_research[n], densities_to_research[d], 100, DIJKSTRA);
				}
				else {
					throw exception("Nie mozna uzyskac dostepu do pliku zapisu");
				}
			}
		}

		dijkstra_list.close();
		dijkstra_matrix.close();
	}

	{
		ofstream prim_list;
		prim_list.open("results_prim_list.txt");

		ofstream prim_matrix;
		prim_matrix.open("results_prim_matrix.txt");

		for (int n = 0; n < nodes_to_research_size; n++) {
			for (int d = 0; d < densities_to_research_size; d++) {
				cout << "Prim N: " << n << " D: " << d << endl;
				if (prim_list && prim_matrix) {
					RunMeasurement(prim_list, prim_matrix, 10, 50, 100, PRIM);
				}
				else {
					throw exception("Nie mozna uzyskac dostepu do pliku zapisu");
				}
			}
		}

		prim_list.close();
		prim_matrix.close();
	}

	{
		ofstream bf_list;
		bf_list.open("results_bf_list.txt");

		ofstream bf_matrix;
		bf_matrix.open("results_bf_matrix.txt");

		for (int n = 0; n < nodes_to_research_size; n++) {
			for (int d = 0; d < densities_to_research_size; d++) {
				cout << "BF N: " << n << " D: " << d << endl;
				if (bf_list && bf_matrix) {
					RunMeasurement(bf_list, bf_matrix, 10, 50, 100, BELLMANFORD);
				}
				else {
					throw exception("Nie mozna uzyskac dostepu do pliku zapisu");
				}
			}
		}

		bf_list.close();
		bf_matrix.close();
	}
}