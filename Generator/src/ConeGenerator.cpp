#include "ConeGenerator.h"

#include <iostream>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

using std::cerr, std::endl, std::stoi, std::stof;

bool ConeGenerator::ParseArguments(int argc, char *argv[]) {
    if(argc < 7) {
        cerr << "Erro: faltam argumentos!" << endl;
        cerr << "Utilização: " << argv[0] << " cone <bottomRadius> <height> <slices> <stacks> <fileName>" << endl;
        return false;
    }

    SetFilename(argv[6]);

  bottomRadius = stoi(argv[2]);
  height = stof(argv[3]);
  slices = stoi(argv[4]);
  stacks = stoi(argv[5]);

    return true;
}

void ConeGenerator::GenerateVertices() {
    double r = double(bottomRadius) / double(stacks);
    double angle = (2 * M_PI) / double(slices);
    double xA, xB, xC, xD, zA, zB, zC, zD;

    glm::vec2 radiusTexture = {bottomRadius/double(2.0 * M_PI * bottomRadius) ,bottomRadius/(double(bottomRadius*2) + height)};

    // Draw base
    for(int i = 0; i < slices; i++) {
        xA = r * stacks * sin(i * angle);
        xB= r * stacks * sin((i + 1) * angle);
        zA = r * stacks * cos(i * angle);
        zB = r * stacks * cos((i + 1) * angle);

        AddVertex({0.0, height - float(stacks) * (height / float(stacks)), 0.0},
                  {0,-1,0},
                     {radiusTexture[0], radiusTexture[1]});
        AddVertex({xB, height - float(stacks) * (height / float(stacks)), zB},
                  {0,-1,0},
                  {radiusTexture[0] + radiusTexture[0] * cos(float(i+1)*angle),radiusTexture[1] + radiusTexture[1] * sin(float(i+1)*angle)});
        AddVertex({xA, height - float(stacks) * (height / float(stacks)), zA},
                  {0,-1,0},
                  {radiusTexture[0] + radiusTexture[0] * cos(float(i)*angle),radiusTexture[1] + radiusTexture[1] * sin(float(i)*angle)});
    }

//    // Draw cone body minus cone tip
//    for(int j = 1; j < stacks; j++) {
//        for(int k = 0; k <= slices; k++) {
//
//            xA = j * r * sin(k * angle);
//            xB = j * r * sin((k + 1) * angle);
//            xC = (j + 1) * r * sin(k * angle);
//            xD = (j + 1) * r * sin((k + 1) * angle);
//            zA = j * r * cos(k * angle);
//            zB = j * r * cos((k + 1) * angle);
//            zC = (j + 1) * r * cos(k * angle);
//            zD = (j + 1) * r * cos((k + 1) * angle);
//
//            AddVertex(xB, height - j * (height / stacks), zB);
//            AddVertex(xA, height - j * (height / stacks), zA);
//            AddVertex(xC, height - (j + 1) * (height / stacks), zC);
//
//            AddVertex(xC, height - (j + 1) * (height / stacks), zC);
//            AddVertex(xD, height - (j + 1) * (height / stacks), zD);
//            AddVertex(xB, height - j * (height / stacks), zB);
//        }
//    }
//
//
//    // Draw cone tip
//    for(int i = 0; i < slices; i++) {
//        xA = r * sin(i * angle);
//        xB = r * sin((i + 1) * angle);
//        zA = r * cos(i * angle);
//        zB = r * cos((i + 1) * angle);
//
//        AddVertex(0.0, height, 0.0);
//        AddVertex(xA, height - (height / stacks), zA);
//        AddVertex(xB, height - (height / stacks), zB);
//    }
}
