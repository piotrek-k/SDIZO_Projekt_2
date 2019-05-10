#pragma once
#include <string>
#include "Node.h"
#include "DijkstraContainer.h"
#include "ListMember.h"

class Container
{
private:

protected:
	int numberOfNodes = 0;
	int numberOfEdges = 0;
	int additionalParam = 0;
	bool isDirected = false;
	void loadFromFile(const std::string& fileName, bool isDirected);
	virtual void declareSize(int numberOfEdges, int numberOfNodes, int additionalParam);
	void generateNodeStorage();
	Node** stateOfNodes = NULL;
public:
	/*Container(const std::string& fileName, bool isDirected);
	Container(int numberOfEdges, int numberOfNodes, int additionalParam, bool isDirected);*/
	~Container();

	// Utw�rz po��czenie mi�dzy w�z�em initialNode a w�z�em endNode o wadze weight
	virtual void InsertNode(int initialNode, int endNode, int weight) = 0;
	// Wy�wietl zawarto�� kontenera
	virtual void Display(std::ostream& stream) = 0;

	//generuje Kontener o wielko�ci obecnego Kontenera
	virtual Container* GenerateEmptyClone() = 0;

	int GetNumberOfNodes();
	int GetNumberOfEdges();
	int GetAdditionalParam();

	// zwraca informacj� o podanym wierzcho�ku grafu
	Node* GetNode(int index);

	// zwraca s�siada danego wierzcho�ka, po��czonego kraw�dzi� o najmniejszym koszcie
	virtual Node* LowestCostNeighbour(int index, bool canBeDisabled) = 0;

	virtual ListMember* GetAllNeighbours(int nodeId) = 0;

	// uruchamia algorytm Prima, zapisuje wynik w podanym Kontenerze
	void RunPrimSaveElsewhere(int startingPoint, Container* targetContainer);

	DijkstraContainer* RunDijkstra(std::ostream& stream, int startingPoint);

	void RefreshActivityOfNodes();
};

