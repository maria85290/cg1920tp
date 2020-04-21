#include "BoxGenerator.h"

#include <iostream>
#include <string>

using std::cerr, std::endl, std::stoi;

bool BoxGenerator::ParseArguments(int argc, char *argv[]) {

    // ./generator box x y z box.3d
    if(argc < 6) {
        cerr << "Faltam argumentos!" << endl;
        cerr << "Utilização: " << argv[0] << " box <dimX> <dimY> <dimZ> <filename>" << endl;

        return false;
    }

    SetFilename(argv[5]); // Número correto de argumentos passado

    dimX = stoi(argv[2]);
    dimY = stoi(argv[3]);
    dimZ = stoi(argv[4]);

    return true;
}

void BoxGenerator::GenerateVertices() {
    
    double y_ = -dimY / 2.0;
    double h = dimZ / 2.0;
    double w = dimX / 2.0;

    // DESENHAR A BASE - plano XZ

    AddVertex(-w, y_, -h);
    AddVertex(w, y_, h);
    AddVertex(-w, y_, h);

    AddVertex(-w, y_, -h);
    AddVertex(w, y_, -h);
    AddVertex(w, y_, h);


    // PARTE SUPERIOR - plano ZX
    y_ = dimY / 2.0;
    AddVertex(-w, y_, -h);
    AddVertex(-w, y_, h);
    AddVertex(w, y_, h);

    AddVertex(-w, y_, -h);
    AddVertex(w, y_, h);
    AddVertex(w, y_, -h);

    //PARTE FRONTAL - plano XY:
    double z_ = dimZ / 2.0;
    w = dimX / 2.0;
    h = dimY / 2.0;
    AddVertex(w, h, z_);
    AddVertex(-w, h, z_);
    AddVertex(-w, -h, z_);

    AddVertex(w, h, z_);
    AddVertex(-w, -h, z_);
    AddVertex(w, -h, z_);


    // Parte de tras plano yx
    z_ = -dimZ / 2.0;
    AddVertex(w, h, z_);
    AddVertex(-w, -h, z_);
    AddVertex(-w, h, z_);

    AddVertex(w, h, z_);
    AddVertex(w, -h, z_);
    AddVertex(-w, -h, z_);

    //lado direito - plano YZ:
    double x_ = dimX / 2.0;
    h = dimY / 2.0;
    w = dimZ / 2.0;

    AddVertex(x_, h, w);
    AddVertex(x_, -h, w);
    AddVertex(x_, -h, -w);

    AddVertex(x_, h, w);
    AddVertex(x_, -h, -w);
    AddVertex(x_, h, -w);

    //lado esquerdo plano zy

    x_ = -dimX / 2.0;

    AddVertex(x_, h, w);
    AddVertex(x_, -h, -w);
    AddVertex(x_, -h, w);

    AddVertex(x_, h, w);
    AddVertex(x_, h, -w);
    AddVertex(x_, -h, -w);
}
