#pragma once
class Node
{
public:
	int index = 0;
	int weight = 0;

	bool active = false;

	Node();

	Node(int index, int weight);
	~Node();

	bool isActive();
	int getWeight();
	int getIndex();
};

