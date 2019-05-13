#pragma once 
#include "Container.h"
#include <fstream>
#include <sstream>
#include "AdjacencyList.h"
#include <math.h>

using namespace std;

const int MAXINT = 2147483647;

//Container::Container(const std::string& fileName, bool isDirected)
//{
//}
//
//Container::Container(int numberOfEdges, int numberOfNodes, int additionalParam, bool isDirected)
//{
//}


Container::Container()
{
}

Container::~Container()
{
}

void Container::loadFromFile(const std::string& fileName, bool isDirected)
{
	this->isDirected = isDirected;
	string line;
	ifstream myfile(fileName);
	bool firstLine = true;
	try {
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				stringstream stream(line);
				int n = 0;
				int values[] = { 0, 0, 0 };

				if (line == "") {
					break;
				}

				stream >> n;
				values[0] = n;

				stream >> n;
				values[1] = n;

				//wartoœæ 3. opcjonalnie
				if (stream >> n) {
					values[2] = n;
				}
				else {
					values[2] = NULL;
				}

				if (firstLine) {
					this->declareSize(values[0], values[1], values[2]);
					firstLine = false;
				}
				else {
					this->InsertNode(values[0], values[1], values[2]);
				}
			}
			myfile.close();
		}
		else {
			throw exception("Wystapil problem z otworzeniem pliku o podanej nazwie");
		}
	}
	catch (std::invalid_argument & e) {
		return;
	}
	catch (const exception & e) {
		throw exception("Wystapil problem z wczytaniem danych z pliku");
	}
}

void Container::declareSize(int numberOfEdges, int numberOfNodes, int additionalParam)
{
	this->numberOfEdges = numberOfEdges;
	this->numberOfNodes = numberOfNodes;
	this->additionalParam = additionalParam;
}

int Container::GetNumberOfNodes()
{
	return numberOfNodes;
}

int Container::GetNumberOfEdges()
{
	return numberOfEdges;
}

int Container::GetAdditionalParam()
{
	return additionalParam;
}

Node* Container::GetNode(int index)
{
	return stateOfNodes[index];
}

void Container::generateNodeStorage()
{
	stateOfNodes = new Node * [numberOfNodes];
	for (int a = 0; a < numberOfNodes; a++) {
		stateOfNodes[a] = new Node(SPECIFIED);
	}

	edgesHeap = new HeapOfEdges();
}

void Container::RunPrimSaveElsewhere(int startingPoint, Container* targetContainer) {
	RefreshActivityOfNodes();

	int numOfIterations = 0;
	this->GetNode(startingPoint)->setActiveState(true);

	while (true) { //numOfIterations < this->GetNumberOfNodes()
		Node minNodeToDisable = Node(EMPTY);
		int sourceNodeIndex = -1;
		int numNodes = this->GetNumberOfNodes();
		for (int a = 0; a < this->GetNumberOfNodes(); a++) {
			if (this->GetNode(a)->isActive() == true) {
				// ten wêze³ by³ ju¿ dodany, szukamy najmniejszej wagi wœród s¹siadów
				Node n = *this->LowestCostNeighbour(a, false);
				if (minNodeToDisable.IsNull() || minNodeToDisable.getWeight() > n.getWeight()) {
					if (n.IsNotNull()) {
						minNodeToDisable = n;
						sourceNodeIndex = a;
					}
				}
			}
		}

		if (minNodeToDisable.IsNotNull()) {
			targetContainer->InsertNode(sourceNodeIndex, minNodeToDisable.getIndex(), minNodeToDisable.getWeight());
			this->GetNode(minNodeToDisable.getIndex())->setActiveState(true);
		}
		else {
			//throw exception("Proba dodania nieprawidlowego indeksu");
			break;
		}

		numOfIterations++;
	}
}

ShortestPathsContainer* Container::RunDijkstra(int startingPoint)
{
	RefreshActivityOfNodes();
	// wartoœæ "active" w ka¿dym Node okreœla w którym podzbiorze znajduje siê wierzcho³ek
	// zbiór Q - false (wartoœæ domyœlna, zbiór wierzcho³ków do sprawdzenia)
	// zbiór S - true (zbiór wierzcho³ków sprawdzonych)

	long long* d = new long long[this->GetNumberOfNodes()]; // koszty dojœcia z 'u' do startingPoint
	int* p = new int[this->GetNumberOfNodes()]; // p[u] - wierzcho³ek bêd¹cy nastêpnym krokiem w kierunku startingPoint

	for (int a = 0; a < this->GetNumberOfNodes(); a++) {
		d[a] = MAXINT;
		p[a] = -1;
	}

	// wierzcho³ek pocz¹tkowy
	//this->GetNode(startingPoint)->active = true;
	d[startingPoint] = 0;

	for (int w = 0; w < this->GetNumberOfNodes(); w++) {
		// znajdŸ najmniejsz¹ wartoœæ w tablicy d, która odpowiada wierzcho³kowi w zbiorze Q
		int minVal = MAXINT;
		int minIndex = -1;
		for (int x = 0; x < this->GetNumberOfNodes(); x++) {
			if (d[x] < minVal && this->GetNode(x)->active == false) {
				minVal = d[x];
				minIndex = x;
			}
		}

		if (minIndex == -1) {
			//throw exception("Wystapila nieprzewidziana sytuacja. Brak wierzcholka do przeniesienia z Q do S.");
			break;
		}
		else {
			this->GetNode(minIndex)->active = true; // przeniesienie wierzcho³ka do S
		}

		ListMember* neighbourToCheck = this->GetAllNeighbours(minIndex);

		while (true) {
			if (neighbourToCheck->IsNotNull() && neighbourToCheck != NULL) {
				if (!this->GetNode(neighbourToCheck->index)->active) {
					// nie ma go w zbiorze Q		
					if (d[neighbourToCheck->index] > d[minIndex] + neighbourToCheck->weight) {
						d[neighbourToCheck->index] = d[minIndex] + neighbourToCheck->weight;
						p[neighbourToCheck->index] = minIndex;
					}
				}

				neighbourToCheck = neighbourToCheck->getNext();
			}
			else {
				break;
			}
		}

	}

	ShortestPathsContainer* dc = new ShortestPathsContainer(d, p, this->GetNumberOfNodes());

	return dc;
}

ShortestPathsContainer* Container::RunBellmanFord(int startingPoint)
{
	long long* d = new long long[this->GetNumberOfNodes()]; // koszty dojœcia z 'u' do startingPoint
	int* p = new int[this->GetNumberOfNodes()]; // p[u] zawiera numer wierzcho³ka który jest poprzednikiem
	for (int a = 0; a < this->GetNumberOfNodes(); a++) {
		d[a] = MAXINT;
		p[a] = -1;
	}

	d[startingPoint] = 0; // koszt dojœcia do wierzcho³ka startowego

	for (int n = 0; n < this->GetNumberOfNodes() - 1; n++) { // wykonaj pêtlê n-1 razy
		bool test = true; // czy coœ zosta³o zmienione?

		for (int x = 0; x < this->GetNumberOfNodes() - 1; x++) {
			ListMember* neighbour = this->GetAllNeighbours(x);
			do {
				if (d[neighbour->getIndex()] > d[x] + neighbour->getWeight()) {
					test = false; // je¿eli doszliœmy tutaj to dokonano zmiany
					d[neighbour->getIndex()] = d[x] + neighbour->getWeight();
					p[neighbour->getIndex()] = x; // ustalamy poprzednik
				}
				neighbour = neighbour->getNext();

			} while (neighbour->IsNotNull());

			if (test == true) {
				//ZAKOÑCZONO POMYŒLNIE
				ShortestPathsContainer* result = new ShortestPathsContainer(d, p, this->GetNumberOfNodes());
				return result;
			}
		}
	}

	// SPRAWDZENIE ISTNIENIA CYKLU
	for (int x = 0; x < this->GetNumberOfNodes() - 1; x++) {
		ListMember* neighbour = this->GetAllNeighbours(x);
		do {
			if (d[neighbour->getIndex()] > d[x] + neighbour->getWeight()) {
				// ZAKOÑCZ Z WYNIKIEM FALSE
				return new ShortestPathsContainer();
			}
			neighbour = neighbour->getNext();
		} while (neighbour->IsNotNull());
	}

}

void Container::RefreshActivityOfNodes()
{
	for (int a = 0; a < GetNumberOfNodes(); a++) {
		stateOfNodes[a]->setActiveState(false);
	}
}
