#include <iostream>
#include <string>
#include <list>
#include <fstream>

#define _USE_MATH_DEFINES

#include <math.h>

#include "Common/vectors.h"

#include "AbstractGenerator.h"

using namespace std;

const int PLANE_XY = 0;
const int PLANE_XZ = 1;
const int PLANE_YZ = 2;

list<vec3> generateSquare(int plane, int width, int height);

list<vec3> generateBox(int dimX, int dimY, int dimZ, int numDiv);

list<vec3> generateSphere(int radius, int slices, int stacks);

list<vec3> generateCone(int bottomRadius, int height, int slices, int stacks);

void saveModel(const list<vec3> &vertices, const string &fileName);

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    cerr << "Não foi especificado um tipo de primitva a gerar!" << endl;
    cerr << "Uso: ./generator <plane/box/sphere/cone> <parameters...>" << endl;

    return 1;
  }

  string primitiveType = argv[1];

  list<vec3> vertices;
  string fileName;

  if (primitiveType == "plane") {

    vertices = generateSquare(plane, stoi(argv[2]), stoi(argv[3]));
  } else if (primitiveType == "box") {
    vertices = generateBox(stoi(argv[2]), stoi(argv[3]), stoi(argv[4]), stoi(argv[5]));
    fileName = argv[6];
  } else if (primitiveType == "sphere") {
    vertices = generateSphere(stoi(argv[2]), stoi(argv[3]), stoi(argv[4]));
    fileName = argv[5];
  } else if (primitiveType == "cone") {
    vertices = generateCone(stoi(argv[2]), stoi(argv[3]), stoi(argv[4]), stoi(argv[5]));
    fileName = argv[6];
  }

  saveModel(vertices, fileName);

  cout << "Saved model to file " << fileName << endl;

  return 0;
}

void saveModel(const list<vec3> &vertices, const string &fileName) {
  fstream file(fileName, fstream::out);

  for (const vec3 &vertex : vertices) {
    file << vertex.x << " "
         << vertex.y << " "
         << vertex.z << endl;
  }

  file.close();
}

void AbstractGenerator::SaveVerticesToFile() {
  fstream file(filename_, fstream::out);

  for (const vec3 &vertex : vertices_) {
    file << vertex.x << " "
         << vertex.y << " "
         << vertex.z << endl;
  }

  file.close();
}
