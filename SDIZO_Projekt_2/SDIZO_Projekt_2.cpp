#include <iostream>
#include<string>
#include "Container.h"
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "ShortestPathsContainer.h"
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include "Measurements.h"

using namespace std;

AdjacencyList* al = new AdjacencyList();
AdjacencyMatrix* am = new AdjacencyMatrix();
AdjacencyList* output_list = new AdjacencyList();
AdjacencyMatrix* output_matrix = new AdjacencyMatrix();

void displayMenu(string info)
{
	cout << endl;
	cout << info << endl;
	cout << "1.Wczytaj z pliku" << endl;
	cout << "2.Generuj losowo" << endl;
	cout << "3.Wyswietl graf wejsciowy" << endl;
	cout << "4.Uruchom algorytm, pokaz wyniki" << endl;
	cout << "0.Powrot do menu" << endl;
	cout << "Podaj opcje:";
}

// funkcja sprawdza czy dane wejœciowe s¹ w porz¹dku
// jeœli nie, wyrzuca wyj¹tek
void validateCin() {
	if (cin.fail()) {
		throw exception("Podana wartosc nieprawidlowa");
	}
}

// cin dzia³a w nieprzewidywalny sposób jeœli podamy
// wartoœæ z³ego typu na strumieñ wejœciowy
// funkcja eliminuje ten problem
void clearCinAfterError() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.sync();
}

// generowanie losowego drzewa. Dowolne dwa wierzcho³ki bêd¹ mia³y ze sob¹ co najwy¿ej jedn¹ krawêdŸ
void generateRandomGraph(int numberOfNodes, int density, AdjacencyList*& al, AdjacencyMatrix*& am, bool directed)
{
	if (numberOfNodes <= 0) {
		throw exception("Nieprawidlowa wartosc ilosci wezlow");
	}

	if (density > 100 || density <= 0) {
		throw exception("Nieprawidlowa wartosc gestosci grafu");
	}

	if (al != nullptr) {
		al->Clean();
	}
	if (am != nullptr) {
		am->Clean();
	}

	srand(time(0));
	int maxNumberOfEdges = numberOfNodes * (numberOfNodes - 1) / 2;
	int edgesToCreate = std::floor(maxNumberOfEdges * (density / 100.0));
	int minNumberOfEdges = numberOfNodes - 1;
	if (edgesToCreate < minNumberOfEdges) {
		throw exception("Graf o podanej gestosci nie bylby grafem spojnym. Podaj inne wartosci.");
	}
	int weightRange = 10;

	al = new AdjacencyList(edgesToCreate, numberOfNodes, 0, directed);
	am = new AdjacencyMatrix(edgesToCreate, numberOfNodes, 0, directed);

	// generowanie drzewa rozpinajacego
	for (int n = 0; n < numberOfNodes - 1 && edgesToCreate > 0; n++) {
		int newWeight = (rand() % weightRange) + 1;
		al->InsertNode(n, n + 1, newWeight);
		am->InsertNode(n, n + 1, newWeight);
		edgesToCreate--;
	}

	// generowanie reszty drzewa
	for (int n = 0; n < edgesToCreate; n++) {
		int randomNode1;
		int randomNode2;
		do {
			randomNode1 = (rand() % numberOfNodes);
			randomNode2 = (rand() % numberOfNodes);
		} while (am->DoesConnectionExist(randomNode1, randomNode2) || randomNode1 == randomNode2);

		int newWeight = (rand() % weightRange) + 1;
		al->InsertNode(randomNode1, randomNode2, newWeight);
		am->InsertNode(randomNode1, randomNode2, newWeight);
	}
}

void finding_path() {
	string fileName; //nazwa pliku wpisana przez u¿ytkownika
	int numberOfNodes; // ile wêz³ów ma mieæ losowy graf?
	int density; // jaka gêstoœæ grafu?
	char option;

	do {
		try {
			cout << endl;
			cout << "==== NAJKROTSZA SCIEZKA ===" << endl;
			cout << "1.Wczytaj wartosci" << endl;
			cout << "2.Utworz graf losowy" << endl;
			cout << "3.Wyœwietl graf" << endl;
			cout << "4.Algorytm Dijkstry" << endl;
			cout << "5.Algorytm Bellmana-Forda" << endl;
			cout << "0.Wyjscie" << endl;
			cout << "Podaj opcje:";

			cin >> option;
			validateCin();
			cout << endl;
			switch (option) {
			case '1':
				// Wczytaj z pliku

				cout << " Podaj nazwe pliku:";
				cin >> fileName;

				cout << "Program zaklada, ze wczytane dane reprezentuja graf skierowany" << endl;
				//cin >> directed;

				al = new AdjacencyList(fileName, true);
				am = new AdjacencyMatrix(fileName, true);

				cout << "Wczytano." << endl << endl;

				if (al != NULL && am != NULL) {
					al->Display(cout);
					am->Display(cout);
				}

				break;
			case '2':

				// generuj losowo

				cout << " Podaj ilosc wezlow grafu:";
				cin >> numberOfNodes;
				cout << " Podaj gestosc grafu (w %):";
				cin >> density;
				cout << "Program zaklada, ze wczytane dane reprezentuja graf skierowany" << endl;

				generateRandomGraph(numberOfNodes, density, al, am, true);
				break;
			case '3':
				// Wyœwietl

				if (al != NULL && am != NULL) {
					al->Display(cout);
					am->Display(cout);
				}
				else {
					cout << "Grafy sa puste" << endl;
				}
				break;

			case '4':
				std::cout << "--- Operacje na listach sasiedztwa \n";
				//DijkstraContainer* dc = 
				al->RunDijkstra(0)->Display(cout);

				std::cout << "--- Operacje na macierzach sasiedztwa \n";
				//DijkstraContainer* dc2 = 
				am->RunDijkstra(0)->Display(cout);
				break;

			case '5':
				std::cout << "--- Operacje na listach sasiedztwa \n";
				//DijkstraContainer* dc = 
				al->RunBellmanFord(0)->Display(cout);

				std::cout << "--- Operacje na macierzach sasiedztwa \n";
				//DijkstraContainer* dc2 = 
				am->RunBellmanFord(0)->Display(cout);
				break;
			}
		}
		catch (const std::exception & e) {
			cout << "program zwrocil blad: " << e.what() << endl;
			clearCinAfterError();
		}
		clearCinAfterError();
	} while (option != '0');
}

void finding_mst() {
	string fileName; //nazwa pliku wpisana przez u¿ytkownika
	int numberOfNodes; // ile wêz³ów ma mieæ losowy graf?
	int density; // jaka gêstoœæ grafu?
	char option;

	do {
		try {
			cout << endl;
			cout << "==== GENEROWANIE DRZEWA MST ===" << endl;
			cout << "1.Wczytaj wartosci" << endl;
			cout << "2.Utworz graf losowy" << endl;
			cout << "3.Wyœwietl graf" << endl;
			cout << "4.Algorytm Prima" << endl;
			cout << "5.Algorytm Kruskala" << endl;
			cout << "0.Wyjscie" << endl;
			cout << "Podaj opcje:";

			cin >> option;
			validateCin();
			cout << endl;
			switch (option) {
			case '1':
				// Wczytaj z pliku

				cout << " Podaj nazwe pliku:";
				cin >> fileName;

				cout << "Program zaklada, ze wczytane dane reprezentuja graf nieskierowany" << endl;

				al = new AdjacencyList(fileName, false);
				am = new AdjacencyMatrix(fileName, false);

				cout << "Wczytano." << endl << endl;

				if (al != NULL && am != NULL) {
					al->Display(cout);
					am->Display(cout);
				}

				break;
			case '2':

				// generuj losowo

				cout << " Podaj ilosc wezlow grafu:";
				cin >> numberOfNodes;
				cout << " Podaj gestosc grafu (w %):";
				cin >> density;
				cout << "Program zaklada, ze wczytane dane reprezentuja graf nieskierowany" << endl;

				generateRandomGraph(numberOfNodes, density, al, am, false);
				break;
			case '3':
				// Wyœwietl

				if (al != NULL && am != NULL) {
					al->Display(cout);
					am->Display(cout);
				}
				else {
					cout << "Grafy sa puste" << endl;
				}
				break;
			case '4':
				std::cout << "--- Operacje na listach sasiedztwa \n";
				output_list = (AdjacencyList*)al->GenerateEmptyClone();
				al->RunPrimSaveElsewhere(0, output_list);
				output_list->Display(cout);

				std::cout << "--- Operacje na macierzach sasiedztwa \n";
				output_matrix = (AdjacencyMatrix*)am->GenerateEmptyClone();
				am->RunPrimSaveElsewhere(0, output_matrix);
				output_matrix->Display(cout);
				break;

			case '5':
				std::cout << "--- Operacje na listach sasiedztwa \n";
				output_list = (AdjacencyList*)al->GenerateEmptyClone();
				al->RunKruskalSaveElsewhere(output_list);
				output_list->Display(cout);

				std::cout << "--- Operacje na macierzach sasiedztwa \n";
				output_matrix = (AdjacencyMatrix*)am->GenerateEmptyClone();
				am->RunKruskalSaveElsewhere(output_matrix);
				output_matrix->Display(cout);
				break;
			}
		}
		catch (const std::exception & e) {
			cout << "program zwrocil blad: " << e.what() << endl;
			clearCinAfterError();
		}
		clearCinAfterError();
	} while (option != '0');
}

int main()
{
	string fileName; //nazwa pliku wpisana przez u¿ytkownika
	bool directed; // czy wczytany graf jest skierowany?
	int numberOfNodes; // ile wêz³ów ma mieæ losowy graf?
	int density; // jaka gêstoœæ grafu?
	char option;

	do {
		try {
			cout << endl;
			cout << "==== MENU GLOWNE ===" << endl;
			cout << "1.Wczytaj wartosci" << endl;
			cout << "2.Utworz graf losowy" << endl;
			cout << "3.Wyœwietl graf" << endl;
			cout << "4.Problem najkrotszej sciezki" << endl;
			cout << "5.Generowanie drzewa MST" << endl;
			cout << "9.Wykonaj pomiary" << endl;
			cout << "0.Wyjscie" << endl;
			cout << "Podaj opcje:";

			cin >> option;
			validateCin();
			cout << endl;
			switch (option) {
			case '1':
				// Wczytaj z pliku

				cout << " Podaj nazwe pliku:";
				cin >> fileName;

				cout << " Czy graf ma byc skierowany? 0 - nie, 1 - tak";
				cin >> directed;

				al = new AdjacencyList(fileName, directed);
				am = new AdjacencyMatrix(fileName, directed);

				cout << "Wczytano." << endl << endl;

				if (al != NULL && am != NULL) {
					al->Display(cout);
					am->Display(cout);
				}
				else {
					cout << "Grafy sa puste" << endl;
				}

				break;
			case '2':

				// generuj losowo

				cout << " Podaj ilosc wezlow grafu:";
				cin >> numberOfNodes;
				cout << " Podaj gestosc grafu (w %):";
				cin >> density;
				cout << " Czy graf ma byc skierowany? 0 - nie, 1 - tak";
				cin >> directed;

				generateRandomGraph(numberOfNodes, density, al, am, directed);
				break;
			case '3':
				// Wyœwietl

				if (al != NULL && am != NULL) {
					al->Display(cout);
					am->Display(cout);
				}
				else {
					cout << "Grafy sa puste" << endl;
				}
				break;
			case '4':
				finding_path();
				break;

			case '5':
				finding_mst();
				break;

			case '9':
				RunAllMeasurements();
				break;
			}
		}
		catch (const std::exception & e) {
			cout << "program zwrocil blad: " << e.what() << endl;
			clearCinAfterError();
		}
		clearCinAfterError();
	} while (option != '0');
}