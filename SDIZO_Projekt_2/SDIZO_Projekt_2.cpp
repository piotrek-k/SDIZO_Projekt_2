#include <iostream>
#include<string>
#include "Container.h"
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "DijkstraContainer.h"
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

using namespace std;

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
	int weightRange = 10;

	al = new AdjacencyList(edgesToCreate, numberOfNodes, 0, directed);
	am = new AdjacencyMatrix(edgesToCreate, numberOfNodes, 0, directed);

	// generowanie drzewa rozpinajacego
	for (int n = 0; n < numberOfNodes - 1 && edgesToCreate > 0; n++) {
		int newWeight = (rand() % weightRange)+1;
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

		int newWeight = (rand() % weightRange)+1;
		al->InsertNode(randomNode1, randomNode2, newWeight);
		am->InsertNode(randomNode1, randomNode2, newWeight);
	}
}

void menu_prim() {
	char opt; //wybrana opcja
	string fileName; //nazwa pliku wpisana przez u¿ytkownika
	bool directed; // czy wczytany graf jest skierowany?
	int numberOfNodes; // ile wêz³ów ma mieæ losowy graf?
	int density; // jaka gêstoœæ grafu?
	AdjacencyList* al = new AdjacencyList();
	AdjacencyMatrix* am = new AdjacencyMatrix();

	do {
		try {
			displayMenu("Algorytm Prima");
			cin >> opt;
			cout << endl;
			switch (opt) {
			case '1':
				// Wczytaj z pliku

				cout << " Podaj nazwe pliku:";
				cin >> fileName;
				//cout << " Jak to typ grafu? (0-nieskierowany, 1-skierowany)";
				//cin >> directed;

				al = new AdjacencyList(fileName, false);
				am = new AdjacencyMatrix(fileName, false);

				cout << "Wczytano." << endl;

				break;
			case '2':

				// generuj losowo

				cout << " Podaj ilosc wezlow grafu:";
				cin >> numberOfNodes;
				cout << " Podaj gestosc grafu (w %):";
				cin >> density;

				generateRandomGraph(numberOfNodes, density, al, am, false);

				break;
			case '3':
				// Wyœwietl

				if (al != NULL && am != NULL) {
					al->Display(cout);
					am->Display(cout);
				}

				break;

			case '4':
				// Uruchom algorytm, pokaz wyniki

				std::cout << "--- Operacje na listach s¹siedztwa \n";
				AdjacencyList* output = (AdjacencyList*)al->GenerateEmptyClone();
				al->RunPrimSaveElsewhere(0, output);
				output->Display(cout);

				std::cout << "--- Operacje na macierzach s¹siedztwa \n";
				AdjacencyMatrix* output_m = (AdjacencyMatrix*)am->GenerateEmptyClone();
				am->RunPrimSaveElsewhere(0, output_m);
				output_m->Display(cout);
			}
		}
		catch (const std::exception & e) {
			cout << "program zwrocil blad: " << e.what() << endl;
			clearCinAfterError();
		}
		clearCinAfterError();
	} while (opt != '0');
}

void menu_dijkstra() {
	char opt; //wybrana opcja
	string fileName; //nazwa pliku wpisana przez u¿ytkownika
	bool directed; // czy wczytany graf jest skierowany?
	int numberOfNodes; // ile wêz³ów ma mieæ losowy graf?
	int density; // jaka gêstoœæ grafu?
	AdjacencyList* al = new AdjacencyList();
	AdjacencyMatrix* am = new AdjacencyMatrix();

	do {
		try {
			displayMenu("Algorytm Dijkstry");
			cin >> opt;
			cout << endl;
			switch (opt) {
			case '1':
				// Wczytaj z pliku

				cout << " Podaj nazwe pliku:";
				cin >> fileName;

				al = new AdjacencyList(fileName, true);
				am = new AdjacencyMatrix(fileName, true);

				cout << "Wczytano." << endl;

				break;
			case '2':

				// generuj losowo

				cout << " Podaj ilosc wezlow grafu:";
				cin >> numberOfNodes;
				cout << " Podaj gestosc grafu (w %):";
				cin >> density;

				generateRandomGraph(numberOfNodes, density, al, am, true);

				break;
			case '3':
				// Wyœwietl

				if (al != NULL && am != NULL) {
					al->Display(cout);
					am->Display(cout);
				}

				break;

			case '4':
				std::cout << "--- Operacje na listach s¹siedztwa \n";
				DijkstraContainer* dc = al->RunDijkstra(cout, 0);

				std::cout << "--- Operacje na macierzach s¹siedztwa \n";
				DijkstraContainer* dc2 = am->RunDijkstra(cout, 0);

			}
		}
		catch (const std::exception & e) {
			cout << "program zwrocil blad: " << e.what() << endl;
			clearCinAfterError();
		}
		clearCinAfterError();
	} while (opt != '0');
}
int main()
{

	char option;
	do {
		cout << endl;
		cout << "==== MENU GLOWNE ===" << endl;
		cout << "1.Algorytm Prima" << endl;
		cout << "2.Algorytm Dijkstry" << endl;
		cout << "5.Wykonaj pomiary" << endl;
		cout << "0.Wyjscie" << endl;
		cout << "Podaj opcje:";

		cin >> option;
		validateCin();
		cout << endl;
		switch (option) {
		case '1':
			menu_prim();
			break;

		case '2':
			menu_dijkstra();
			break;

		case '5':
			//tC.Start(210, 10, 50, 100, cout);
			break;
		default:
			cout << "Nie znaleziono takiej opcji";
		}
		clearCinAfterError();
	} while (option != '0');
}