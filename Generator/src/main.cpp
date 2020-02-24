#include <iostream>
#include <string>
#include <list>

#define _USE_MATH_DEFINES
#include <math.h>

#include "common/"

using namespace std;

#define PLANE_XY 0
#define PLANE_XZ 1
#define PLANE_YZ 2

list<vec3> generatePlane(int plane, int width, int height);
void generate

int main(int argc, char* argv[]) {
	if (argc <= 1) {
		cerr << "Não foi especificado um tipo de primitva a gerar!" << endl;
		cerr << "Uso: ./generator <plane/box/sphere/cone> <parameters...>" << endl;

		return 1;
	}

	string primitiveType(argv[1]);

	if (primitiveType == "plane") {
		generatePlane(PLANE_XZ, stoi(argv[2]), stoi(argv[3]));
	}
	else if (primitiveType == "box") {
		generateBox(stoi(argv[2]), stoi(argv[3]), stoi(argv[4]), stoi(argv[5]));
	}

	return 0;
}

