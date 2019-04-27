#pragma once
#include "Container.h"
class PrimAlgorithm
{
	Container* inputData;
	Container* outputData;
	bool* alreadyChosenNodes; // tablica przechowuj�ca ju� dodane wierzcho�ki
	void run(int startingPoint);

public:
	PrimAlgorithm(Container* data, Container* outData, int startingPoint);
	~PrimAlgorithm();

	Container* GetResult();
};

