#include "BezierGenerator.h"

#include <iostream>
#include <string>

using namespace std;

bool BezierGenerator::ParseArguments(int argc, char* argv[]) {

    if(argc < 5) {
        cerr << "Faltam argumentos!" << endl;
        cerr << "Utilização: " << argv[0] << " bezier  <file_read> <tessellation_level> <filename>" << endl;

        return false;
    }

    SetFilename(argv[4]); //nome do ficheiro, onde será guardado

    this->patchFilename = argv[2];
    this->tessellationLevel = stoi(argv[3]);

    /*
Formato do ficheiro, "patchs":
1º - numero de patches
2º - reprentação de todos os patchs (cada um tem 16 indices)
3º - Numero total de pontos de controlo
4º - Lista com todas as coordenadas dos pontos de controlo
*/

    ifstream file(this->patchFilename);

    int numPatches;
    file >> numPatches;

    for(int i = 0; i < numPatches; i++) {
        std::vector<int> patch;
        patch.reserve(16);

        for(int j = 0; j < 16; j++) {
            int index;
            file >> index;
            file.ignore(1);
            patch.push_back(index);
        }

        this->patches.push_back(patch);
    }

    int numControlPoints;
    file >> numControlPoints;

    for(int i = 0; i < numControlPoints; i++) {
        glm::vec4 point(1.0f);

        file >> point.x;
        file.ignore(1);
        file >> point.y;
        file.ignore(1);
        file >> point.z;
        file.ignore(1);

        this->controlPoints.push_back(point);
    }

    file.close();

    return true;
}

void BezierGenerator::GenerateVertices() {
    // Calcular os pontos (tendo como referencia os varios valores de u e v de acordo com o nivel de tessellation
    const float step = 1.0f / float(tessellationLevel);

    for(int i = 0; i < this->patches.size(); i++) {
        auto patch = this->patches[i];

        for(float u = 0; u < 1.0; u += step) {
            for(float v = 0; v < 1.0; v += step) {
                auto p0 = this->ComputePatchPoint(u, v, patch);
                auto p1 = this->ComputePatchPoint(u, v + step, patch);
                auto p2 = this->ComputePatchPoint(u + step, v, patch);
                auto p3 = this->ComputePatchPoint(u + step, v + step, patch);

                AddVertex(p3);
                AddVertex(p2);
                AddVertex(p1);

                AddVertex(p2);
                AddVertex(p0);
                AddVertex(p1);
            }
        }
    }
}

const glm::vec4 BezierGenerator::ComputePatchPoint(float u, float v,
                                                   const glm::vec4& p00, const glm::vec4& p01, const glm::vec4& p02, const glm::vec4& p03,
                                                   const glm::vec4& p10, const glm::vec4& p11, const glm::vec4& p12, const glm::vec4& p13,
                                                   const glm::vec4& p20, const glm::vec4& p21, const glm::vec4& p22, const glm::vec4& p23,
                                                   const glm::vec4& p30, const glm::vec4& p31, const glm::vec4& p32, const glm::vec4& p33
) const {
    const glm::vec4 U = {powf(u, 3), powf(u, 2), u, 1.0f};

    static const glm::mat4 M = {
        {-1.0f, 3.0f, -3.0f, 1.0f},
        {3.0f, -6.0f, 3.0f, 0.0f},
        {-3.0f, 3.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f, 0.0f}
    };

    const vmat4 P = {
        {p00, p10, p20, p30},
        {p01, p11, p21, p31},
        {p02, p12, p22, p32},
        {p03, p13, p23, p33}
    };

    const glm::vec4 V = {powf(v, 3), powf(v, 2), v, 1.0f};

    return U * M * transpose(P) * M * V;
}
