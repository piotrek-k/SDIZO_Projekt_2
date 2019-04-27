#pragma once 
#include "Container.h"
#include <fstream>
#include <sstream>
#include "AdjacencyList.h"

using namespace std;

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
		stateOfNodes[a] = new Node();
	}
}

void Container::RunPrimSaveElsewhere(int startingPoint, Container* targetContainer) {
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
				if (minNodeToDisable.isNull() || minNodeToDisable.getWeight() > n.getWeight()) {
					if (n.isNotNull()) {
						minNodeToDisable = n;
						sourceNodeIndex = a;
					}
				}
			}
		}

		if (minNodeToDisable.isNotNull()) {
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