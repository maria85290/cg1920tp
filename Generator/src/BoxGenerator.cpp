#include "BoxGenerator.h"

#include <iostream>
#include <string>
#include <algorithm>

using std::cerr, std::endl, std::stoi, std::max;

bool BoxGenerator::ParseArguments(int argc, char *argv[]) {

    // ./generator box x y z box.3d
    if(argc < 6) {
        cerr << "Faltam argumentos!" << endl;
        cerr << "Utilização: " << argv[0] << " box <dimX> <dimY> <dimZ> <filename>" << endl;

        return false;
    }

    SetFilename(argv[5]);

    dimX = stoi(argv[2]);
    dimY = stoi(argv[3]);
    dimZ = stoi(argv[4]);

    return true;
}

void BoxGenerator::GenerateVertices() {
    double h = dimY / 2.0;
    double w = dimX / 2.0;
    double d = dimZ / 2.0;

    double textureImageHeight = max(dimY, dimZ);
    double textureImageWidth = 4*dimX + 2*dimZ;

    // Current left bottom corner and right top corner, respectively
    glm::vec2 lbc = {0.0f, float(dimY)}, rtc = {float(dimZ),0.0f};

    // Parallel with plane ZY
    AddVertex({w,-h,d},{1,0,0},{lbc[0]/textureImageWidth,lbc[1]/textureImageHeight});
    AddVertex({w,-h,-d},{1,0,0},{rtc[0]/textureImageWidth,lbc[1]/textureImageHeight});
    AddVertex({w,h,-d},{1,0,0},{rtc[0]/textureImageWidth,rtc[1]/textureImageHeight});

    AddVertex({w,-h,d},{1,0,0},{lbc[0]/textureImageWidth,lbc[1]/textureImageHeight});
    AddVertex({w,h,-d},{1,0,0},{rtc[0]/textureImageWidth,rtc[1]/textureImageHeight});
    AddVertex({w,h,d},{1,0,0},{lbc[0]/textureImageWidth,rtc[1]/textureImageHeight});

    lbc[0] += float(dimZ);
    rtc[0] += float(dimZ);


    // Parallel with plane YZ
    AddVertex({-w,-h,d},{-1,0,0},{rtc[0]/textureImageWidth,lbc[1]/textureImageHeight});
    AddVertex({-w,h,-d},{-1,0,0},{lbc[0]/textureImageWidth,rtc[1]/textureImageHeight});
    AddVertex({-w,-h,-d},{-1,0,0},{lbc[0]/textureImageWidth,lbc[1]/textureImageHeight});

    AddVertex({-w,-h,d},{-1,0,0},{rtc[0]/textureImageWidth,lbc[1]/textureImageHeight});
    AddVertex({-w,h,d},{-1,0,0},{rtc[0]/textureImageWidth,rtc[1]/textureImageHeight});
    AddVertex({-w,h,-d},{-1,0,0},{lbc[0]/textureImageWidth,rtc[1]/textureImageHeight});

    lbc[0] += float(dimZ);
    rtc[0] += float(dimX);


    // Parallel with plane XY
    AddVertex({-w,-h,d},{0,0,1},{lbc[0]/textureImageWidth,lbc[1]/textureImageHeight});
    AddVertex({w,h,d},{0,0,1},{rtc[0]/textureImageWidth,rtc[1]/textureImageHeight});
    AddVertex({-w,h,d},{0,0,1},{lbc[0]/textureImageWidth,rtc[1]/textureImageHeight});

    AddVertex({-w,-h,d},{0,0,1},{lbc[0]/textureImageWidth,lbc[1]/textureImageHeight});
    AddVertex({w,-h,d},{0,0,1},{rtc[0]/textureImageWidth,lbc[1]/textureImageHeight});
    AddVertex({w,h,d},{0,0,1},{rtc[0]/textureImageWidth,rtc[1]/textureImageHeight});

    lbc[0] += float(dimX);
    rtc[0] += float(dimX);


    // Parallel with plane YX
    AddVertex({-w,-h,-d},{0,0,-1},{rtc[0]/textureImageWidth,lbc[1]/textureImageHeight});
    AddVertex({-w,h,-d},{0,0,-1},{rtc[0]/textureImageWidth,rtc[1]/textureImageHeight});
    AddVertex({w,h,-d},{0,0,-1},{lbc[0]/textureImageWidth,rtc[1]/textureImageHeight});

    AddVertex({-w,-h,-d},{0,0,-1},{rtc[0]/textureImageWidth,lbc[1]/textureImageHeight});
    AddVertex({w,h,-d},{0,0,-1},{lbc[0]/textureImageWidth,rtc[1]/textureImageHeight});
    AddVertex({w,-h,-d},{0,0,-1},{lbc[0]/textureImageWidth,lbc[1]/textureImageHeight});

    lbc[0] += float(dimX);
    lbc[1] = float(dimZ);
    rtc[0] += float(dimX);


    // Parallel with plane XZ
    AddVertex({w,h,d},{0,1,0},{rtc[0]/textureImageWidth,lbc[1]/textureImageHeight});
    AddVertex({w,h,-d},{0,1,0},{rtc[0]/textureImageWidth,rtc[1]/textureImageHeight});
    AddVertex({-w,h,-d},{0,1,0},{lbc[0]/textureImageWidth,rtc[1]/textureImageHeight});

    AddVertex({w,h,d},{0,1,0},{rtc[0]/textureImageWidth,lbc[1]/textureImageHeight});
    AddVertex({-w,h,-d},{0,1,0},{lbc[0]/textureImageWidth,rtc[1]/textureImageHeight});
    AddVertex({-w,h,d},{0,1,0},{lbc[0]/textureImageWidth,lbc[1]/textureImageHeight});

    lbc[0] += float(dimX);
    rtc[0] += float(dimX);


    // Parallel with plane ZX
    AddVertex({w,-h,d},{0,-1,0},{rtc[0]/textureImageWidth,rtc[1]/textureImageHeight});
    AddVertex({-w,-h,-d},{0,-1,0},{lbc[0]/textureImageWidth,lbc[1]/textureImageHeight});
    AddVertex({w,-h,-d},{0,-1,0},{rtc[0]/textureImageWidth,lbc[1]/textureImageHeight});

    AddVertex({w,-h,d},{0,-1,0},{rtc[0]/textureImageWidth,rtc[1]/textureImageHeight});
    AddVertex({-w,-h,d},{0,-1,0},{lbc[0]/textureImageWidth,rtc[1]/textureImageHeight});
    AddVertex({-w,-h,-d},{0,-1,0},{lbc[0]/textureImageWidth,lbc[1]/textureImageHeight});
}
