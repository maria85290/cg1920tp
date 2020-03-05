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
    double x, x2, z, z2, x3, x4, z3, z4;

    for(int i = 0; i < slices_; i++) {
        x = r * sin(i * angle);
        x2 = r * sin((i + 1) * angle);
        z = r * cos(i * angle);
        z2 = r * cos((i + 1) * angle);

        AddVertex(0.0, height_, 0.0);
        AddVertex(x, height_ - (height_ / stacks), z);
        AddVertex(x2, height_ - (height_ / stacks), z2);
    }

    for(int j = 1; j < stacks; j++) {
        for(int k = 0; k <= slices_; k++) {

            x = j * r * sin(k * angle);
            x2 = j * r * sin((k + 1) * angle);
            x3 = (j + 1) * r * sin(k * angle);
            x4 = (j + 1) * r * sin((k + 1) * angle);
            z = j * r * cos(k * angle);
            z2 = j * r * cos((k + 1) * angle);
            z3 = (j + 1) * r * cos(k * angle);
            z4 = (j + 1) * r * cos((k + 1) * angle);

            AddVertex(x2, height_ - j * (height_ / stacks), z2);
            AddVertex(x, height_ - j * (height_ / stacks), z);
            AddVertex(x3, height_ - (j + 1) * (height_ / stacks), z3);

            AddVertex(x3, height_ - (j + 1) * (height_ / stacks), z3);
            AddVertex(x4, height_ - (j + 1) * (height_ / stacks), z4);
            AddVertex(x2, height_ - j * (height_ / stacks), z2);
        }
    }

    for(int i = 0; i < slices_; i++) {
        x = r * stacks * sin(i * angle);
        x2 = r * stacks * sin((i + 1) * angle);
        z = r * stacks * cos(i * angle);
        z2 = r * stacks * cos((i + 1) * angle);

        AddVertex(0.0, height_ - stacks * (height_ / stacks), 0.0);
        AddVertex(x2, height_ - stacks * (height_ / stacks), z2);
        AddVertex(x, height_ - stacks * (height_ / stacks), z);
    }

}
