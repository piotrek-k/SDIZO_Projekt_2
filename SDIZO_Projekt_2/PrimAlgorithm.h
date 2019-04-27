#pragma once
#include "Container.h"
class PrimAlgorithm
{
	Container* inputData;
	Container* outputData;
	bool* alreadyChosenNodes; // tablica przechowuj¹ca ju¿ dodane wierzcho³ki
	void run(int startingPoint);

public:
	PrimAlgorithm(Container* data, Container* outData, int startingPoint);
	~PrimAlgorithm();

	Container* GetResult();
};

