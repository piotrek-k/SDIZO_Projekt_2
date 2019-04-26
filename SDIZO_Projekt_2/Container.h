#pragma once
#include <string>

class Container
{
public:
	Container();
	~Container();

	void LoadFromFile(std::string fileName);
	virtual void InsertNode(int initialNode, int endNode, int weight) = 0;
	virtual void DeclareSize(int numberOfEdges, int numberOfNodes, int additionalParam) = 0;
	virtual void Display(std::ostream& stream) = 0;
};

