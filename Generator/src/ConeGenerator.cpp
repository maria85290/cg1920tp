#include "ConeGenerator.h"
#define _USE_MATH_DEFINES
#include <math.h>
bool ConeGenerator::ParseArguments(int argc, char *argv[]) {
 
    SetFilename(argv[6]); // Número correto de argumentos passado

    bottomRadius_ = stoi(argv[2]);
    height_ = stoi(argv[3]);
    slices_ = stoi(argv[4]);
    stacks_ = stoi(argv[5]);

    return true;
}

void ConeGenerator::GenerateVertices() {
    double r = bottomRadius_/ stacks_;
    float s = r;
    double angle = (2*M_PI)/slices_;
    double x, x2, z, z2, x3, x4, z3, z4;

    for(int i = 0; i < slices_; i++){
        x = r*sin(i*angle);
        x2 = r*sin((i+1)*angle);
        z = r*cos(i*angle);
        z2 = r*cos((i+1)*angle);

        AddVertex(0.0, height_, 0.0);
        AddVertex(x, height_-(height_/stacks_), z);
        AddVertex(x2, height_-(height_/stacks_), z2);
    }


    for (int j = 1; j < stacks_; j++){
        for (int k = 0; k <= slices_; k++){

            x = j*r*sin(k*angle);
            x2 = j*r*sin((k+1)*angle);
            x3 = (j+1)*r*sin(k*angle);
            x4 = (j+1)*r*sin((k+1)*angle);
            z = j*r*cos(k*angle);
            z2 = j*r*cos((k+1)*angle);
            z3 = (j+1)*r*cos(k*angle);
            z4 = (j+1)*r*cos((k+1)*angle);

            AddVertex(x2, height_-j*(height_/stacks_), z2);
            AddVertex(x, height_-j*(height_/stacks_), z);
            AddVertex(x3, height_-(j+1)*(height_/stacks_), z3);

            AddVertex(x3, height_-(j+1)*(height_/stacks_), z3);
            AddVertex(x4, height_-(j+1)*(height_/stacks_), z4);
            AddVertex(x2, height_-j*(height_/stacks_), z2);
        }
    }

    for(int i = 0; i < slices_; i++){
        x = r*stacks_*sin(i*angle);
        x2 = r*stacks_*sin((i+1)*angle);
        z = r*stacks_*cos(i*angle);
        z2 = r*stacks_*cos((i+1)*angle);

        AddVertex(0.0, height_-stacks_*(height_/stacks_), 0.0);
        AddVertex(x, height_-stacks_*(height_/stacks_), z);
        AddVertex(x2,height_-stacks_*(height_/stacks_), z2);
    }

}
