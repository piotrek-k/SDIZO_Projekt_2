#pragma once
#include <string>
#include "Node.h"
#include "ShortestPathsContainer.h"
#include "ListMember.h"
#include "HeapOfEdges.h"
#include "Edge.h"

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
	// KRUSKAL
	HeapOfEdges* edgesHeap = new HeapOfEdges();

	/*Container(const std::string& fileName, bool isDirected);
	Container(int numberOfEdges, int numberOfNodes, int additionalParam, bool isDirected);*/
	Container();
	~Container();

	// Utw�rz po��czenie mi�dzy w�z�em initialNode a w�z�em endNode o wadze weight
	virtual void InsertEdge(int initialNode, int endNode, int weight, bool enableEdgesHeap = true) = 0;
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

	// uruchamia algorytm Prima, zapisuje wynik w podanym Kontenerze, zwraca wag� drzewa
	int RunPrimSaveElsewhere(int startingPoint, Container* targetContainer);

	// funkcja powi�zana z algorytmem Kruskala. ��czy dwa drzewa
	void KruskalUnionSets(Node* node1, Node* node2);

	// Uruchamia algorytm Kruskala, zwraca wag� nowego drzewa
	int RunKruskalSaveElsewhere(Container* targetContainer);

	ShortestPathsContainer* RunDijkstra(int startingPoint);

	ShortestPathsContainer* RunBellmanFord(int startingPoint);

	// Usuwa dane z obecnej instancji, generuje nowy graf maj�cy `numberOfNodes` wierzcho�k�w
	// `density` oznacza ilo�� kraw�dzi wyra�ona w procentach maksymalnej ich liczby
	//void GenerateRandomGraph(int numberOfNodes, int density);

	// Usuwa dane z obecnej instancji
	virtual void Clean() = 0;

	void RefreshActivityOfNodes();

	virtual bool DoesConnectionExist(int node1, int node2) = 0;
};

