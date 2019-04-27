#pragma once 
#include "Container.h"
#include <fstream>
#include <sstream>
#include "AdjacencyList.h"

using namespace std;

Container::Container(const std::string& fileName, bool isDirected)
{
}

Container::Container(int numberOfEdges, int numberOfNodes, int additionalParam, bool isDirected)
{
	/*this->DeclareSize(numberOfEdges, numberOfNodes, additionalParam);
	this->isDirected = isDirected;*/
}


Container::~Container()
{
}

void Container::LoadFromFile(const std::string& fileName, bool isDirected)
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
					this->DeclareSize(values[0], values[1], values[2]);
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

void Container::DeclareSize(int numberOfEdges, int numberOfNodes, int additionalParam)
{
	this->numberOfEdges = numberOfEdges;
	this->numberOfNodes = numberOfNodes;
	this->additionalParam = additionalParam;
	this->nodesActivity = new bool[numberOfNodes];
	for (int a = 0; a < numberOfNodes; a++) {
		this->nodesActivity[a] = true;
	}
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

void Container::RunPrimSaveElsewhere(int startingPoint, Container* targetContainer) {
	int numOfIterations = 0;
	this->GetNode(startingPoint)->active = true;

	while (true) { //numOfIterations < this->GetNumberOfNodes()
		Node minNodeToDisable = Node(-1, -1);
		int sourceNodeIndex = -1;
		int numNodes = this->GetNumberOfNodes();
		for (int a = 0; a < this->GetNumberOfNodes(); a++) {
			if (this->GetNode(a)->active == true) {
				// ten wêze³ by³ ju¿ dodany, szukamy najmniejszej wagi wœród s¹siadów
				Node n = *this->LowestCostNeighbour(a, false);
				if (minNodeToDisable.index == -1 || minNodeToDisable.weight > n.weight) {
					if (n.index != -1) {
						minNodeToDisable = n;
						sourceNodeIndex = a;
					}
				}
			}
		}

		if (minNodeToDisable.index != -1) {
			targetContainer->InsertNode(sourceNodeIndex, minNodeToDisable.index, minNodeToDisable.weight);
			this->GetNode(minNodeToDisable.index)->active = true;
		}
		else {
			//throw exception("Proba dodania nieprawidlowego indeksu");
			break;
		}

		numOfIterations++;
	}
}