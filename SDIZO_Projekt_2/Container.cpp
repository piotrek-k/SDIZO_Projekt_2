#pragma once 
#include "Container.h"
#include <fstream>
#include <sstream>
#include "AdjacencyList.h"

using namespace std;

const int MAXINT = 2147483647;

//Container::Container(const std::string& fileName, bool isDirected)
//{
//}
//
//Container::Container(int numberOfEdges, int numberOfNodes, int additionalParam, bool isDirected)
//{
//}


Container::~Container()
{
}

void Container::loadFromFile(const std::string& fileName, bool isDirected)
{
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

DijkstraContainer* Container::RunDijkstra(std::ostream& stream, int startingPoint)
{
	RefreshActivityOfNodes();
	// wartoœæ "active" w ka¿dym Node okreœla w którym podzbiorze znajduje siê wierzcho³ek
	// zbiór Q - false (wartoœæ domyœlna, zbiór wierzcho³ków do sprawdzenia)
	// zbiór S - true (zbiór wierzcho³ków sprawdzonych)

	int* d = new int[this->GetNumberOfNodes()]; // koszty dojœcia z 'u' do startingPoint
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

	stream << "d: ";
	for (int a = 0; a < this->GetNumberOfNodes(); a++) {
		stream << d[a] << " ";
	}
	stream << endl;

	stream << "p: ";
	for (int a = 0; a < this->GetNumberOfNodes(); a++) {
		stream << p[a] << " ";
	}
	stream << endl;

	// wyniki
	int* stos = new int[this->GetNumberOfNodes()];
	int stos_wsk = 0;
	for (int a = 0; a < this->GetNumberOfNodes(); a++) {
		stream << a << ": ";

		for (int j = a; j > -1; j = p[j]) {
			stos[stos_wsk++] = j;
		}
		while (stos_wsk) stream << stos[--stos_wsk] << " ";
		stream << "$" << d[a] << endl;
	}

	DijkstraContainer* dc = new DijkstraContainer();
	dc->minCostTable = d;
	dc->prevStepsTable = p;

	return dc;
}

void Container::GenerateRandomGraph(int numberOfNodes, int density)
{

}

void Container::RefreshActivityOfNodes()
{
	for (int a = 0; a < GetNumberOfNodes(); a++) {
		stateOfNodes[a]->setActiveState(false);
	}
}
