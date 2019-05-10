#pragma once
enum NodeType {
	EMPTY, SPECIFIED
};
// reprezentuje wierzcho³ek lub informacje o krawêdzi
class Node
{
private:
public:
	bool initialized = false;
	int weight = 0;
	int index = 0;
	bool active = false;

	Node();
	Node(NodeType isNull);
	Node(int index, int weight);
	~Node();

	bool isActive();
	void setActiveState(bool active);
	int getWeight();
	int getIndex();

	bool IsNull();
	bool IsNotNull();
};

