#include <iostream>

#include "PlaneGenerator.h"

using namespace std;

bool PlaneGenerator::ParseArguments(int argc, char *argv[]) {
    plane_ = kPlaneXZ;

    // Minor parsing para manter compatibilidade com aquilo que o stor pediu
    if(argc > 5) {
        // O utilizador especificou o plano no qual construir o retângulo

        string planeName = argv[4];

        if(planeName == "xy")
            plane_ = kPlaneXY;
        else if(planeName == "xz")
            plane_ = kPlaneXZ;
        else if(planeName == "yz")
            plane_ = kPlaneYZ;
        else {
            cerr << "Plano " << planeName << " não definido!" << endl
                 << "Planos possívels: xy, xz, yz" << endl;

            return false;
        }

        SetFilename(argv[5]);
    } else if(argc < 5) { // Número incorreto de argumentos passado
        cerr << "Faltam argumentos!" << endl
             << "Utilização: ./Gerador plane <width> <height> [xy|xz|yz]" << endl;

        return false;
    } else
        SetFilename(argv[4]); // Número correto de argumentos passado

    width_ = stoi(argv[2]);
    height_ = stoi(argv[3]);

    return true;
}

void PlaneGenerator::GenerateVertices() {
    double w = width_ / 2.0;
    double h = height_ / 2.0;

    switch(plane_) {
        case kPlaneYZ:AddVertex(0.0, w, -h);
            AddVertex(0.0, -w, -h);
            AddVertex(0.0, -w, h);

            AddVertex(0.0, w, -h);
            AddVertex(0.0, -w, h);
            AddVertex(0.0, w, h);

            break;
        case kPlaneXZ:AddVertex(w, 0.0, -h);
            AddVertex(-w, 0.0, -h);
            AddVertex(-w, 0.0, h);

            AddVertex(w, 0.0, -h);
            AddVertex(-w, 0.0, h);
            AddVertex(w, 0.0, h);

            break;
        case kPlaneXY:AddVertex(w, -h, 0.0);
            AddVertex(-w, -h, 0.0);
            AddVertex(-w, h, 0.0);

            AddVertex(w, -h, 0.0);
            AddVertex(-w, h, 0.0);
            AddVertex(w, h, 0.0);

            break;
    }
}
