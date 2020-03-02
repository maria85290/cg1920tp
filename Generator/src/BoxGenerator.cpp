#include <iostream>
#include <string>

#include "BoxGenerator.h"

bool BoxGenerator::ParseArguments(int argc, char *argv[]) {

    // ./generator box x y z box.3d
    if(argc < 6) {
        cerr << "Faltam argumentos!" << endl;
        cerr << "Utilização: " << argv[0] << " box <dimX> <dimY> <dimZ> <filename>" << endl;

        return false;
    }

    SetFilename(argv[5]); // Número correto de argumentos passado

    dimX_ = stoi(argv[2]);
    dimY_ = stoi(argv[3]);
    dimZ_ = stoi(argv[4]);

    return true;
}

void BoxGenerator::GenerateVertices() {
    double y_ = -dimY_ / 2.0;
    double h = dimZ_ / 2.0;
    double w = dimX_ / 2.0;

    // DESENHAR A BASE - plano XZ

    AddVertex(-w, y_, -h);
    AddVertex(w, y_, h);
    AddVertex(-w, y_, h);

    AddVertex(-w, y_, -h);
    AddVertex(w, y_, -h);
    AddVertex(w, y_, h);


    // PARTE SUPERIOR - plano ZX
    y_ = dimY_ / 2.0;
    AddVertex(-w, y_, -h);
    AddVertex(-w, y_, h);
    AddVertex(w, y_, h);

    AddVertex(-w, y_, -h);
    AddVertex(w, y_, h);
    AddVertex(w, y_, -h);

    //PARTE FRONTAL - plano XY:
    double z_ = dimZ_ / 2.0;
    w = dimX_ / 2.0;
    h = dimY_ / 2.0;
    AddVertex(w, h, z_);
    AddVertex(-w, h, z_);
    AddVertex(-w, -h, z_);

    AddVertex(w, h, z_);
    AddVertex(-w, -h, z_);
    AddVertex(w, -h, z_);


    // Parte de tras plano yx
    z_ = -dimZ_ / 2.0;
    AddVertex(w, h, z_);
    AddVertex(-w, -h, z_);
    AddVertex(-w, h, z_);

    AddVertex(w, h, z_);
    AddVertex(w, -h, z_);
    AddVertex(-w, -h, z_);

    //lado direito - plano YZ:
    double x_ = dimX_ / 2.0;
    h = dimY_ / 2.0;
    w = dimZ_ / 2.0;

    AddVertex(x_, h, w);
    AddVertex(x_, -h, w);
    AddVertex(x_, -h, -w);

    AddVertex(x_, h, w);
    AddVertex(x_, -h, -w);
    AddVertex(x_, h, -w);

    //lado esquerdo plano zy

    x_ = -dimX_ / 2.0;

    AddVertex(x_, h, w);
    AddVertex(x_, -h, -w);
    AddVertex(x_, -h, w);

    AddVertex(x_, h, w);
    AddVertex(x_, h, -w);
    AddVertex(x_, -h, -w);
}
