#pragma once
#include <string>

class Container
{
protected:
	int numberOfNodes = 0;
	int numberOfEdges = 0;
	bool isDirected = false;
public:
	Container();
	~Container();

	void LoadFromFile(std::string fileName);
	virtual void InsertNode(int initialNode, int endNode, int weight) = 0;
	virtual void DeclareSize(int numberOfEdges, int numberOfNodes, int additionalParam) = 0;
	virtual void Display(std::ostream& stream) = 0;
};

