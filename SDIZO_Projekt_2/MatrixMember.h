#pragma once
#include "Node.h"

class MatrixMember : Node
{
public:
	MatrixMember();
	~MatrixMember();

	bool connection = false;
	int weight = 0;
};

