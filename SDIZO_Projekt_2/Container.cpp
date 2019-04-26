#include "Container.h"
#include <fstream>
#include <sstream>

using namespace std;

Container::Container()
{
}

Container::Container(bool isDirected)
{
	this->isDirected = isDirected;
}


Container::~Container()
{
}

void Container::LoadFromFile(std::string fileName)
{
	string line;
	ifstream myfile(fileName);
	bool firstLine = true;
	try {
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				stringstream stream(line);
				int n = 0;
				int values[] = { 0, 0, 0 };

				stream >> n;
				values[0] = n;

				stream >> n;
				values[1] = n;

				//wartoœæ 3. opcjonalnie
				if (stream >> n) {
					values[2] = n;
				}
				else {
					values[2] = NULL;
				}

				if (firstLine) {
					this->DeclareSize(values[0], values[1], values[2]);
					firstLine = false;
				}
				else {
					this->InsertNode(values[0], values[1], values[2]);
				}
			}
			myfile.close();
		}
		else {
			throw exception("Wystapil problem z otworzeniem pliku o podanej nazwie");
		}
	}
	catch (std::invalid_argument & e) {
		return;
	}
	catch (const exception & e) {
		throw exception("Wystapil problem z wczytaniem danych z pliku");
	}
}

void Container::DeclareSize(int numberOfEdges, int numberOfNodes, int additionalParam)
{
	this->numberOfEdges = numberOfEdges;
	this->numberOfNodes = numberOfNodes;
}
