#include <iostream>

#include <string>
#include "BoxGenerator.h"
#include "PlaneGenerator.h"
bool BoxGenerator::ParseArguments(int argc, char* argv[]) {
   
    // ./generator box x y z box.3d
    if (argc < 6) {
        cerr << "Nao foram definidos todos os argumentos" << endl;

        return false;
     }

    SetFilename(argv[5]); // Número correto de argumentos passado

    dimX_ = stoi(argv[2]);
    dimY_ = stoi(argv[3]);
    dimZ_ = stoi(argv[4]);

    return true;
}


void BoxGenerator::GenerateVertices() {
   
    //static PlaneGenerator pbase;
    //pbase.incializarVar(2, dimX_, dimY_,0,0,0);
    //pbase.GenerateVertices();




    float y_ = - dimY_/2.0;
    float h = dimZ_/2.0;
    float w = dimX_/2.0;
    
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
    float z_ = dimZ_ / 2.0;
    w = dimX_/2.0;
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
    float x_ = dimX_ / 2.0;
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


