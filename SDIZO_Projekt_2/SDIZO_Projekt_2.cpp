#include <iostream>
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"

using namespace std;

int main()
{
    std::cout << "non directed AdjacencyList: \n"; 
	AdjacencyList* al = new AdjacencyList(false);
	al->LoadFromFile("dane_droga.txt");
	al->Display(cout);

	std::cout << "directed AdjacencyList: \n";
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
	am->Display(cout);
}