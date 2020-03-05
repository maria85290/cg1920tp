#include <iostream>

#include "ConeGenerator.h"

#define _USE_MATH_DEFINES
#include <math.h>

bool ConeGenerator::ParseArguments(int argc, char *argv[]) {
    if(argc < 7) {
        cerr << "Erro: faltam argumentos!" << endl;
        cerr << "Utilização: " << argv[0] << " cone <bottomRadius> <height> <slices> <stacks> <fileName>" << endl;
        return false;
    }

    SetFilename(argv[6]);

    bottomRadius_ = stoi(argv[2]);
    height_ = stoi(argv[3]);
    slices_ = stoi(argv[4]);
    stacks_ = stoi(argv[5]);

    return true;
}

void ConeGenerator::GenerateVertices() {
    double stacks = stacks_; // Implicit type cast; prevents loss of precision when performing integer divisions

    double r = bottomRadius_ / stacks;
    double angle = (2 * M_PI) / slices_;
    double xA, xB, xC, xD, zA, zB, zC, zD;

    for(int i = 0; i < slices_; i++) {
        xA = r * sin(i * angle);
        xB = r * sin((i + 1) * angle);
        zA = r * cos(i * angle);
        zB = r * cos((i + 1) * angle);

        AddVertex(0.0, height_, 0.0);
        AddVertex(xA, height_ - (height_ / stacks), zA);
        AddVertex(xB, height_ - (height_ / stacks), zB);
    }

    for(int j = 1; j < stacks; j++) {
        for(int k = 0; k <= slices_; k++) {

            xA = j * r * sin(k * angle);
            xB = j * r * sin((k + 1) * angle);
            xC = (j + 1) * r * sin(k * angle);
            xD = (j + 1) * r * sin((k + 1) * angle);
            zA = j * r * cos(k * angle);
            zB = j * r * cos((k + 1) * angle);
            zC = (j + 1) * r * cos(k * angle);
            zD = (j + 1) * r * cos((k + 1) * angle);

            AddVertex(xB, height_ - j * (height_ / stacks), zB);
            AddVertex(xA, height_ - j * (height_ / stacks), zA);
            AddVertex(xC, height_ - (j + 1) * (height_ / stacks), zC);

            AddVertex(xC, height_ - (j + 1) * (height_ / stacks), zC);
            AddVertex(xD, height_ - (j + 1) * (height_ / stacks), zD);
            AddVertex(xB, height_ - j * (height_ / stacks), zB);
        }
    }

    for(int i = 0; i < slices_; i++) {
        xA = r * stacks * sin(i * angle);
        xB= r * stacks * sin((i + 1) * angle);
        zA = r * stacks * cos(i * angle);
        zB = r * stacks * cos((i + 1) * angle);

        AddVertex(0.0, height_ - stacks * (height_ / stacks), 0.0);
        AddVertex(xB, height_ - stacks * (height_ / stacks), zB);
        AddVertex(xA, height_ - stacks * (height_ / stacks), zA);
    }

}
