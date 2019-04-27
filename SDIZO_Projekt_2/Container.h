#pragma once
#include <string>
#include "Node.h"

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
	
public:
	/*Container(const std::string& fileName, bool isDirected);
	Container(int numberOfEdges, int numberOfNodes, int additionalParam, bool isDirected);*/
	~Container();

	virtual void InsertNode(int initialNode, int endNode, int weight) = 0;
	virtual void Display(std::ostream& stream) = 0;

	//generuje Kontener o wielkoœci obecnego Kontenera
	virtual Container* GenerateEmptyClone() = 0;

	int GetNumberOfNodes();
	int GetNumberOfEdges();
	int GetAdditionalParam();

	// zwraca informacjê o podanym wierzcho³ku grafu
	virtual Node* GetNode(int index) = 0;

	// szuka minimalnego wierzcho³ka grafu
	virtual Node* LowestCostNeighbour(int index, bool canBeDisabled) = 0;

	// uruchamia algorytm Prima, zapisuje wynik w podanym Kontenerze
	void RunPrimSaveElsewhere(int startingPoint, Container* targetContainer);
};

