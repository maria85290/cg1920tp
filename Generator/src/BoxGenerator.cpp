#include <iostream>
#include <string>

#include "BoxGenerator.h"

bool BoxGenerator::ParseArguments(int argc, char* argv[]) {
   
    // ./generator box x y z box.3d
    if (argc < 6) {
        cerr << "Nao foram definidos todos os argumentos" << endl;

        return false;
     }

    SetFilename(argv[5]); // Número correto de argumentos passado

    dimX_ = stoi(argv[2]) ;
    dimY_ = stoi(argv[3]);;
    dimZ_ = stoi(argv[4]);;

    return true;
}

void BoxGenerator::GenerateVertices() {
 
}
