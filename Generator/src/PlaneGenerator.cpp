#include "PlaneGenerator.h"

#include <iostream>
#include <string>

using std::cerr, std::endl, std::stoi, std::string;

bool PlaneGenerator::ParseArguments(int argc, char *argv[]) {
    plane = kPlaneXZ;

    // Minor parsing para manter compatibilidade com aquilo que o stor pediu
    if(argc > 5) {
        // O utilizador especificou o plano no qual construir o retângulo

        const string planeName = argv[4];

        if(planeName == "xy")
            plane = kPlaneXY;
        else if(planeName == "yx")
            plane = kPlaneYX;
        else if(planeName == "xz")
            plane = kPlaneXZ;
        else if(planeName == "zx")
            plane = kPlaneZX;
        else if(planeName == "yz")
            plane = kPlaneYZ;
        else if(planeName == "zy")
            plane = kPlaneZY;
        else {
            cerr << "Plano " << planeName << " não definido!" << endl
                 << "Planos possívels: xy, yx, xz, zx, yz, zy" << endl;

            return false;
        }

        SetFilename(argv[5]);
    } else if(argc < 5) { // Número incorreto de argumentos passado
        cerr << "Erro: faltam argumentos!" << endl
             << "Utilização: " << argv[0] << " plane <width> <height> [xy|yx|xz|zx|yz|zy] <fileName>" << endl;

        return false;
    } else {
        SetFilename(argv[4]); // Número correto de argumentos passado
    }

    width = stoi(argv[2]);
    height = stoi(argv[3]);

    return true;
}

void PlaneGenerator::GenerateVertices() {
    double w = width / 2.0;
    double h = height / 2.0;

    switch(plane) {
        case kPlaneYZ:
            AddVertex({0.0, h, w}, {-1, 0, 0}, {0, 0});
            AddVertex({0.0, -h, w}, {-1, 0, 0}, {0, 1});
            AddVertex({0.0, -h, -w}, {-1, 0, 0}, {1, 1});

            AddVertex({0.0, h, w}, {-1, 0, 0}, {0, 0});
            AddVertex({0.0, -h, -w}, {-1, 0, 0}, {1, 1});
            AddVertex({0.0, h, -w}, {-1, 0, 0}, {1, 0});

            break;

        case kPlaneZY:
            AddVertex({0.0, h, w}, {1, 0, 0}, {1, 0});
            AddVertex({0.0, -h, -w}, {1, 0, 0}, {0, 1});
            AddVertex({0.0, -h, w}, {1, 0, 0}, {1, 1});

            AddVertex({0.0, h, w}, {1, 0, 0}, {1, 0});
            AddVertex({0.0, h, -w}, {1, 0, 0}, {0, 0});
            AddVertex({0.0, -h, -w}, {1, 0, 0}, {0, 1});

            break;

        case kPlaneXZ:
            AddVertex({-w, 0.0, -h}, {0, 1, 0}, {0, 1});
            AddVertex({w, 0.0, h}, {0, 1, 0}, {1, 0});
            AddVertex({-w, 0.0, h}, {0, 1, 0}, {0, 0});

            AddVertex({-w, 0.0, -h}, {0, 1, 0}, {0, 1});
            AddVertex({w, 0.0, -h}, {0, 1, 0}, {1, 1});
            AddVertex({w, 0.0, h}, {0, 1, 0}, {1, 0});

            break;

        case kPlaneZX:
            AddVertex({-w, 0.0, -h}, {0, -1, 0}, {1, 1});
            AddVertex({-w, 0.0, h}, {0, -1, 0}, {1, 0});
            AddVertex({w, 0.0, h}, {0, -1, 0}, {0, 0});

            AddVertex({-w, 0.0, -h}, {0, -1, 0}, {1, 1});
            AddVertex({w, 0.0, h}, {0, -1, 0}, {0, 0});
            AddVertex({w, 0.0, -h}, {0, -1, 0}, {0, 1});

            break;

        case kPlaneXY:
            AddVertex({w, h, 0.0}, {0, 0, 1}, {1, 0});
            AddVertex({-w, h, 0.0}, {0, 0, 1}, {0, 0});
            AddVertex({-w, -h, 0.0}, {0, 0, 1}, {0, 1});

            AddVertex({w, h, 0.0}, {0, 0, 1}, {1, 0});
            AddVertex({-w, -h, 0.0}, {0, 0, 1}, {0, 1});
            AddVertex({w, -h, 0.0}, {0, 0, 1}, {1, 1});

            break;

        case kPlaneYX:
            AddVertex({w, h, 0.0}, {0, 0, -1}, {0, 0});
            AddVertex({-w, -h, 0.0}, {0, 0, -1}, {1, 1});
            AddVertex({-w, h, 0.0}, {0, 0, -1}, {1, 0});

            AddVertex({w, h, 0.0}, {0, 0, -1}, {0, 0});
            AddVertex({w, -h, 0.0}, {0, 0, -1}, {0, 1});
            AddVertex({-w, -h, 0.0}, {0, 0, -1}, {1, 1});

            break;
    }
}
