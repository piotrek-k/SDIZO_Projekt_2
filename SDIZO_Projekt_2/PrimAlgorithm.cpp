#include "PrimAlgorithm.h"
#include "Node.h"
using namespace std;




PrimAlgorithm::PrimAlgorithm(Container* data, Container* outData, int startingPoint)
{
	inputData = data;
	outputData = outData;
	alreadyChosenNodes = new bool[data->GetNumberOfNodes()];
	for (int a = 0; a < data->GetNumberOfNodes(); a++) {
		alreadyChosenNodes[a] = false;
	}

	run(startingPoint);
}

PrimAlgorithm::~PrimAlgorithm()
{
}

Container* PrimAlgorithm::GetResult()
{
	return outputData;
}

void PrimAlgorithm::run(int startingPoint)
{
	//int numOfIterations = 0;
	//alreadyChosenNodes[startingPoint] = true;

	//while (numOfIterations < inputData->GetNumberOfNodes()) {
	//	Node minNodeToDisable = Node(-1, -1);
	//	for (int a = 0; a < inputData->GetNumberOfNodes(); a++) {
	//		if (alreadyChosenNodes[a] == true) {
	//			// ten wêze³ by³ ju¿ dodany, szukamy najmniejszej wagi wœród s¹siadów
	//			Node n = inputData->LowestCostNeighbour(startingPoint, false);
	//			if (minNodeToDisable.index == -1 || minNodeToDisable.weight < n.weight) {
	//				minNodeToDisable = n;
	//			}
	//		}
	//	}

	//	if (minNodeToDisable.index != -1) {
	//		outputData->InsertNode(startingPoint, minNodeToDisable.index, minNodeToDisable.weight);
	//		alreadyChosenNodes[minNodeToDisable.index] = true;
	//	}
	//	else {
	//		throw exception("Proba dodania nieprawidlowego indeksu");
	//	}

	//	numOfIterations++;
	//}

}
