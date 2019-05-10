#include <iostream>
#include<string>
#include "Container.h"
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "DijkstraContainer.h"

using namespace std;

int main()
{
    std::cout << "non directed AdjacencyList: \n"; 
	AdjacencyList* al = new AdjacencyList("dane_z_eduinf.txt", true);
	al->Display(cout);

	std::cout << "AdjacencyList Prim alg: \n";
	AdjacencyList* output = (AdjacencyList*)al->GenerateEmptyClone();
	al->RunPrimSaveElsewhere(0, output);
	output->Display(cout);

	AdjacencyMatrix* am = new AdjacencyMatrix("dane_z_eduinf.txt", true);
	am->Display(cout);

	std::cout << "AdjacencyList Prim alg: \n";
	AdjacencyMatrix* output_m = (AdjacencyMatrix*)am->GenerateEmptyClone();
	am->RunPrimSaveElsewhere(0, output_m);
	output_m->Display(cout);

	/*std::cout << "directed AdjacencyList: \n";
	AdjacencyMatrix* al = new AdjacencyMatrix("dijkstra_dane_z_eduinf.txt", true);
	al->Display(cout);

	std::cout << "AdjacencyList dijkstra alg: \n";
	DijkstraContainer* dc = al->RunDijkstra(cout, 0);*/


	/*std::cout << "directed AdjacencyList: \n";
	al = new AdjacencyList(true);
	al->LoadFromFile("dane_droga.txt");
	al->Display(cout);

	std::cout << "non directed AdjacencyMatrix: \n";
	AdjacencyMatrix* am = new AdjacencyMatrix(false);
	am->LoadFromFile("dane_droga.txt");
	am->Display(cout);

	std::cout << "directed AdjacencyMatrix: \n";
	am = new AdjacencyMatrix(true);
	am->LoadFromFile("dane_droga.txt");
	am->Display(cout);*/
}