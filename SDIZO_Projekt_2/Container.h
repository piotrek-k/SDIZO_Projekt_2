#pragma once
#include <string>
#include "Node.h"

class Container
{
protected:
	int numberOfNodes = 0;
	int numberOfEdges = 0;
	int additionalParam = 0;
	bool isDirected = false;
	
public:
	Container(const std::string& fileName, bool isDirected);
	Container(int numberOfEdges, int numberOfNodes, int additionalParam, bool isDirected);
	~Container();

	void LoadFromFile(const std::string& fileName, bool isDirected);
	virtual void InsertNode(int initialNode, int endNode, int weight) = 0;
	virtual void DeclareSize(int numberOfEdges, int numberOfNodes, int additionalParam);
	virtual void Display(std::ostream& stream) = 0;
	virtual Container* GenerateEmptyClone() = 0;

	virtual Node* LowestCostNeighbour(int index, bool canBeDisabled) = 0;

	int GetNumberOfNodes();
	int GetNumberOfEdges();
	int GetAdditionalParam();

	virtual Node* GetNode(int index) = 0;

	void RunPrimSaveElsewhere(int startingPoint, Container* targetContainer);

	//PRIM
	bool* nodesActivity = NULL; // true by default
};

