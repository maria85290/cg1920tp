#include "BezierGenerator.h"

#include <iostream>
#include <string>
#include <sstream>

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
    Formato do ficheiro de patches:
    1º - Número de patches
    2º - Índices dos vértices de cada patch; 1 patch por linha
    3º - Número total de pontos de controlo
    4º - Coordenadas dos pontos de controlo; 1 ponto por linha
    */

    ifstream file(this->patchFilename);

    int numPatches;
    file >> numPatches;
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    for(int i = 0; i < numPatches; i++) {
        std::vector<int> patch;
        patch.reserve(16);

        string line;
        getline(file, line);

        stringstream lineStream(line);

        for(int j = 0; j < 16; j++) {
            int index;
            lineStream >> index;
            lineStream.ignore(numeric_limits<streamsize>::max(), ',');

            patch.push_back(index);
        }

        this->patches.push_back(patch);
    }

    int numControlPoints;
    file >> numControlPoints;
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    for(int i = 0; i < numControlPoints; i++) {
        glm::vec4 point(1.0f);

        string line;
        getline(file, line);

        stringstream lineStream(line);

        lineStream >> point.x;
        lineStream.ignore(numeric_limits<streamsize>::max(), ',');

        lineStream >> point.y;
        lineStream.ignore(numeric_limits<streamsize>::max(), ',');

        lineStream >> point.z;

        this->controlPoints.push_back(point);
    }

    file.close();

    return true;
}

void BezierGenerator::GenerateVertices() {
    // step é o valor de quanto u e v têm de andar para a frente, e é definido de acordo com o nível de tesselação
    const float step = 1.0f / float(tessellationLevel);

    for(int i = 0; i < this->patches.size(); i++) {
        auto patch = this->patches[i];

        for(float u = 0; u < 1.0; u += step) {
            for(float v = 0; v < 1.0; v += step) {
                auto [p0, d0] = this->ComputePatchPoint(u, v, patch);
                auto [p1, d1] = this->ComputePatchPoint(u, v + step, patch);
                auto [p2, d2] = this->ComputePatchPoint(u + step, v, patch);
                auto [p3, d3] = this->ComputePatchPoint(u + step, v + step, patch);

                AddVertex(p3, d3, {0.0f, 0.0f});
                AddVertex(p2, d2, {0.0f, 0.0f});
                AddVertex(p1, d1, {0.0f, 0.0f});

                AddVertex(p2, d2, {0.0f, 0.0f});
                AddVertex(p0, d0, {0.0f, 0.0f});
                AddVertex(p1, d1, {0.0f, 0.0f});
            }
        }
    }
}

const pair<glm::vec3, glm::vec3> BezierGenerator::ComputePatchPoint(float u, float v,
                                                   const glm::vec4& p00, const glm::vec4& p01, const glm::vec4& p02, const glm::vec4& p03,
                                                   const glm::vec4& p10, const glm::vec4& p11, const glm::vec4& p12, const glm::vec4& p13,
                                                   const glm::vec4& p20, const glm::vec4& p21, const glm::vec4& p22, const glm::vec4& p23,
                                                   const glm::vec4& p30, const glm::vec4& p31, const glm::vec4& p32, const glm::vec4& p33
) const {
    const glm::vec4 U = {powf(u, 3), powf(u, 2), u, 1.0f};
    const glm::vec4 UPrime = {3 * powf(u, 2), 2 * u, 1.0f, 0.0f};

    static const glm::mat4 M = {
        {-1.0f, 3.0f, -3.0f, 1.0f},
        {3.0f, -6.0f, 3.0f, 0.0f},
        {-3.0f, 3.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f, 0.0f}
    };

    // This matrix must be defined as column-major; each line here represents a column in standard form
    // Each line here also defines a 4x4 matrix itself. However, that definition is being done in a line-major format
    // Therefore, we must transpose each of the 4x4 sub-matrices individually, so they become column-major
    const vmat4 P = transposeEach({
        {p00, p10, p20, p30},
        {p01, p11, p21, p31},
        {p02, p12, p22, p32},
        {p03, p13, p23, p33}
    });

    const glm::vec4 V = {powf(v, 3), powf(v, 2), v, 1.0f};
    const glm::vec4 VPrime = {3 * powf(v, 2), 2 * v, 1.0f, 0.0f};

    const glm::vec3 partialU = UPrime * M * P * M * V;
    const glm::vec3 partialV = U * M * P * M * VPrime;

    return {U * M * P * M * V, partialV * partialU};
}
