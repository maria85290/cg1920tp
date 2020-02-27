#include <iostream>

#include "PlaneGenerator.h"

using namespace std;

bool PlaneGenerator::ParseArguments(int argc, char *argv[]) {
    plane_ = kPlaneXZ;

    // Minor parsing para manter compatibilidade com aquilo que o stor pediu
    if(argc > 5) {
        // O utilizador especificou o plano no qual construir o retângulo

        const string planeName = argv[4];

        if(planeName == "xy")
            plane_ = kPlaneXY;
        else if(planeName == "yx")
            plane_ = kPlaneYX;
        else if(planeName == "xz")
            plane_ = kPlaneXZ;
        else if(planeName == "zx")
            plane_ = kPlaneZX;
        else if(planeName == "yz")
            plane_ = kPlaneYZ;
        else if(planeName == "zy")
            plane_ = kPlaneZY;
        else {
            cerr << "Plano " << planeName << " não definido!" << endl
                 << "Planos possívels: xy, yx, xz, zx, yz, zy" << endl;

            return false;
        }

        SetFilename(argv[5]);
    } else if(argc < 5) { // Número incorreto de argumentos passado
        cerr << "Faltam argumentos!" << endl
             << "Utilização: ./Gerador plane <width> <height> [xy|yx|xz|zx|yz|zy]" << endl;

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
        case kPlaneYZ:
            AddVertex(0.0, h, w);
            AddVertex(0.0, -h, w);
            AddVertex(0.0, -h, -w);

            AddVertex(0.0, h, w);
            AddVertex(0.0, -h, -w);
            AddVertex(0.0, h, -w);
            break;

        case kPlaneZY:
            AddVertex(0.0, h, w);
            AddVertex(0.0, -h, -w);
            AddVertex(0.0, -h, w);

            AddVertex(0.0, h, w);
            AddVertex(0.0, h, -w);
            AddVertex(0.0, -h, -w);
            break;

        case kPlaneXZ:
            AddVertex(-w, 0.0, -h);
            AddVertex(w, 0.0, h);
            AddVertex(-w, 0.0, h);

            AddVertex(-w, 0.0, -h);
            AddVertex(w, 0.0, -h);
            AddVertex(w, 0.0, h);
            break;

        case kPlaneZX:
            AddVertex(-w, 0.0, -h);
            AddVertex(-w, 0.0, h);
            AddVertex(w, 0.0, h);

            AddVertex(-w, 0.0, -h);
            AddVertex(w, 0.0, h);
            AddVertex(w, 0.0, -h);
            break;

        case kPlaneXY:
            AddVertex(w, h, 0.0);
            AddVertex(-w, h, 0.0);
            AddVertex(-w, -h, 0.0);

            AddVertex(w, h, 0.0);
            AddVertex(-w, -h, 0.0);
            AddVertex(w, -h, 0.0);
            break;

        case kPlaneYX:
            AddVertex(w, h, 0.0);
            AddVertex(-w, -h, 0.0);
            AddVertex(-w, h, 0.0);

            AddVertex(w, h, 0.0);
            AddVertex(w, -h, 0.0);
            AddVertex(-w, -h, 0.0);
            break;
    }
}
