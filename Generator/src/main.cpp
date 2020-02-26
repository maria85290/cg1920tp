#include <iostream>
#include <string>

#include "AbstractGenerator.h"
#include "PlaneGenerator.h"
#include "BoxGenerator.h"
#include "SphereGenerator.h"
#include "ConeGenerator.h"

using namespace std;

int main(int argc, char *argv[]) {
    if(argc <= 1) {
        cerr << "Não foi especificado um tipo de primitva a gerar!" << endl;
        cerr << "Uso: ./Generator <plane/box/sphere/cone> <parameters...> <filename>" << endl;

        return 1;
    }

    string primitiveType = argv[1];

    AbstractGenerator *generator = nullptr;

    if(primitiveType == "plane") {
        generator = new PlaneGenerator;
    } else if(primitiveType == "box") {
        generator = new BoxGenerator;
    } else if(primitiveType == "sphere") {
        generator = new SphereGenerator;
    } else if(primitiveType == "cone") {
        generator = new ConeGenerator;
    } else {
        // ERROR!
        return 2;
    }

    if(!generator->ParseArguments(argc, argv)) {
        return -1;
    }

    generator->GenerateVertices();
    generator->SaveVerticesToFile();

    cout << "Saved model to file " << generator->GetFilename() << endl;

    delete generator;

    return 0;
}
