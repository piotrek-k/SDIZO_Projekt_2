#pragma once
enum NodeType {
	EMPTY, SPECIFIED
};
// reprezentuje wierzcho³ek lub informacje o krawêdzi
class Node
{
private:
	bool nullNode = false; // zak³adamy ¿e wierzcho³ek zawiera dane
	
public:
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

	bool isNull();
	bool isNotNull();
};

