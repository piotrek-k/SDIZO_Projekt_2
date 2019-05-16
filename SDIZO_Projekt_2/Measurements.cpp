#include "SDIZO_Projekt_2.h"
#include "timeCounter.h"
#include <iostream>
#include <fstream>

using namespace std;

enum ALGORITHM_TYPE {
	PRIM,
	DIJKSTRA,
	BELLMANFORD,
	KRUSKAL
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
	string typeName = "";

	switch (type) {
	case DIJKSTRA:
		directed = true;
		typeName = "DIJKSTRA";
		break;
	case BELLMANFORD:
		directed = true;
		typeName = "BELLMANFORD";
		break;
	case PRIM:
		directed = false;
		typeName = "PRIM";
		break;
	case KRUSKAL:
		directed = false;
		typeName = "KRUSKAL";
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

			break;

		case KRUSKAL:
			output_al = (AdjacencyList*)al->GenerateEmptyClone();
			adjListCounter->StartNextMeasurement();
			al->RunKruskalSaveElsewhere(output_al);
			adjListCounter->EndSingleMeasurement();
			delete output_al;

			output_am = (AdjacencyMatrix*)am->GenerateEmptyClone();
			adjMatrixCounter->StartNextMeasurement();
			am->RunKruskalSaveElsewhere(output_am);
			adjMatrixCounter->EndSingleMeasurement();
			delete output_am;

			break;

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

	stream1 << numberOfNodes << "\t" << density << "\t" << howManyTimes << "\t" << adjListCounter->Summarize() << "\tL\t" << typeName << std::endl;
	stream2 << numberOfNodes << "\t" << density << "\t" << howManyTimes << "\t" << adjMatrixCounter->Summarize() << "\tM\t" << typeName << std::endl;

	delete al;
	delete am;
}

void RunAllMeasurements() {
	int find_path_nodes_to_research[] = { 10, 20, 30, 40, 50 };
	int MST_nodes_to_research[] = { 10, 20, 30, 40, 50 };
	const int nodes_to_research_size = 5;
	int densities_to_research[] = { 25, 50, 75, 99 };
	const int densities_to_research_size = 4;

	int how_many_times = 100;

	ofstream results_file;
	results_file.open("RESULTS.txt");

	{
		/*ofstream dijkstra_list;
		dijkstra_list.open("results_dijkstra_list.txt");

		ofstream dijkstra_matrix;
		dijkstra_matrix.open("results_dijkstra_matrix.txt");*/

		for (int n = 0; n < nodes_to_research_size; n++) {
			for (int d = 0; d < densities_to_research_size; d++) {
				cout << "Dijkstra N: " << n << " D: " << d << endl;

				if (results_file) {
					RunMeasurement(results_file, results_file, find_path_nodes_to_research[n], densities_to_research[d], how_many_times, DIJKSTRA);
				}
				else {
					throw exception("Nie mozna uzyskac dostepu do pliku zapisu");
				}
			}
		}

		/*dijkstra_list.close();
		dijkstra_matrix.close();*/
	}

	{
		/*ofstream prim_list;
		prim_list.open("results_prim_list.txt");

		ofstream prim_matrix;
		prim_matrix.open("results_prim_matrix.txt");*/

		for (int n = 0; n < nodes_to_research_size; n++) {
			for (int d = 0; d < densities_to_research_size; d++) {
				cout << "Prim N: " << n << " D: " << d << endl;
				if (results_file) {
					RunMeasurement(results_file, results_file, MST_nodes_to_research[n], densities_to_research[d], how_many_times, PRIM);
				}
				else {
					throw exception("Nie mozna uzyskac dostepu do pliku zapisu");
				}
			}
		}

		/*prim_list.close();
		prim_matrix.close();*/
	}

	{
		/*ofstream kruskal_list;
		kruskal_list.open("results_kruskal_list.txt");

		ofstream kruskal_matrix;
		kruskal_matrix.open("results_kruskal_matrix.txt");
*/
		for (int n = 0; n < nodes_to_research_size; n++) {
			for (int d = 0; d < densities_to_research_size; d++) {
				cout << "Kruskal N: " << n << " D: " << d << endl;
				if (results_file) {
					RunMeasurement(results_file, results_file, MST_nodes_to_research[n], densities_to_research[d], how_many_times, KRUSKAL);
				}
				else {
					throw exception("Nie mozna uzyskac dostepu do pliku zapisu");
				}
			}
		}

		/*kruskal_list.close();
		kruskal_matrix.close();*/
	}

	{
		/*ofstream bf_list;
		bf_list.open("results_bf_list.txt");

		ofstream bf_matrix;
		bf_matrix.open("results_bf_matrix.txt");*/

		for (int n = 0; n < nodes_to_research_size; n++) {
			for (int d = 0; d < densities_to_research_size; d++) {
				cout << "BF N: " << n << " D: " << d << endl;
				if (results_file) {
					RunMeasurement(results_file, results_file, find_path_nodes_to_research[n], densities_to_research[d], how_many_times, BELLMANFORD);
				}
				else {
					throw exception("Nie mozna uzyskac dostepu do pliku zapisu");
				}
			}
		}

		/*bf_list.close();
		bf_matrix.close();*/
	}

	results_file.close();
}