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
        glm::dvec4 point(1.0);

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
    const double step = 1.0 / double(tessellationLevel);

    for(int i = 0; i < this->patches.size(); i++) {
        auto patch = this->patches[i];

        for(double u = 0.0000000001; u < 1.0; u += step) {
            for(double v = 0.0000000001; v < 1.0; v += step) {
                auto [p0, d0] = this->ComputePatchPoint(patch, u, v);
                auto [p1, d1] = this->ComputePatchPoint(patch, u, v + step);
                auto [p2, d2] = this->ComputePatchPoint(patch, u + step, v);
                auto [p3, d3] = this->ComputePatchPoint(patch, u + step, v + step);

                AddVertex(p3, d3, {0.0, 0.0});
                AddVertex(p2, d2, {0.0, 0.0});
                AddVertex(p1, d1, {0.0, 0.0});

                AddVertex(p2, d2, {0.0, 0.0});
                AddVertex(p0, d0, {0.0, 0.0});
                AddVertex(p1, d1, {0.0, 0.0});
            }
        }
    }
}

const pair<glm::dvec3, glm::dvec3> BezierGenerator::ComputePatchPoint(double u, double v,
                                                   const glm::dvec4& p00, const glm::dvec4& p01, const glm::dvec4& p02, const glm::dvec4& p03,
                                                   const glm::dvec4& p10, const glm::dvec4& p11, const glm::dvec4& p12, const glm::dvec4& p13,
                                                   const glm::dvec4& p20, const glm::dvec4& p21, const glm::dvec4& p22, const glm::dvec4& p23,
                                                   const glm::dvec4& p30, const glm::dvec4& p31, const glm::dvec4& p32, const glm::dvec4& p33
) const {
    const glm::dvec4 U = {u * u * u, u * u, u, 1.0};
    const glm::dvec4 UPrime = {3 * u * u, 2 * u, 1.0, 0.0};

    static const glm::dmat4 M = {
        {-1.0, 3.0, -3.0, 1.0},
        {3.0, -6.0, 3.0, 0.0},
        {-3.0, 3.0, 0.0, 0.0},
        {1.0, 0.0, 0.0, 0.0}
    };

    // This matrix must be defined as column-major; each line here represents a column in standard form
    // Each line here also defines a 4x4 matrix itself. However, that definition is being done in a line-major format
    // Therefore, we must transpose each of the 4x4 sub-matrices individually, so they become column-major
    const vdmat4 P = transposeEach({
        {p00, p10, p20, p30},
        {p01, p11, p21, p31},
        {p02, p12, p22, p32},
        {p03, p13, p23, p33}
    });

    const glm::dvec4 V = {v * v * v, v * v, v, 1.0};
    const glm::dvec4 VPrime = {3 * v * v, 2 * v, 1.0, 0.0};

    const glm::dvec3 partialU = UPrime * M * P * M * V;
    const glm::dvec3 partialV = (U * M * P) * (M * VPrime);

    return {U * M * P * M * V, glm::cross(partialV, partialU)};
}
