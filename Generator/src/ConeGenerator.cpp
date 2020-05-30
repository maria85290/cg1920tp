#include "ConeGenerator.h"

#include <iostream>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

using std::cerr, std::endl, std::stoi, std::stof, std::atan;

bool ConeGenerator::ParseArguments(int argc, char* argv[]) {
    if(argc < 7) {
        cerr << "Erro: faltam argumentos!" << endl;
        cerr << "Utilização: " << argv[0] << " cone <bottomRadius> <height> <slices> <stacks> <fileName>" << endl;
        return false;
    }

    SetFilename(argv[6]);

    bottomRadius = stof(argv[2]);
    height = stof(argv[3]);
    slices = stoi(argv[4]);
    stacks = stoi(argv[5]);

    return true;
}

void ConeGenerator::GenerateVertices() {
    double r = double(bottomRadius) / double(stacks);
    double angle = (2 * M_PI) / double(slices);
    double textureHeight = double(bottomRadius * 2) + height;
    double textureWidth = 2.0 * M_PI * bottomRadius;

    glm::vec2 radiusTexture = {bottomRadius / textureWidth, bottomRadius / textureHeight};
    glm::vec3 A, B, C, D, AB, AC, BC, DB, DC;

    double textureConeBodyOffsetY = radiusTexture[1] * 2;


    // Draw base
    for(int i = 0; i < slices; i++) {
        A = {r * stacks * sin(i * angle), height - float(stacks) * (height / float(stacks)),
             r * stacks * cos(i * angle)};
        B = {r * stacks * sin((i + 1) * angle), height - float(stacks) * (height / float(stacks)),
             r * stacks * cos((i + 1) * angle)};
        C = {0.0, height - float(stacks) * (height / float(stacks)), 0.0};

        AddVertex(C,
                  {0, -1, 0},
                  {radiusTexture[0], radiusTexture[1]});
        AddVertex(B,
                  {0, -1, 0},
                  {radiusTexture[0] + radiusTexture[0] * cos(float(i + 1) * angle),
                   radiusTexture[1] + radiusTexture[1] * sin(float(i + 1) * angle)});
        AddVertex(A,
                  {0, -1, 0},
                  {radiusTexture[0] + radiusTexture[0] * cos(float(i) * angle),
                   radiusTexture[1] + radiusTexture[1] * sin(float(i) * angle)});
    }


    // Draw cone body minus cone tip, starting top down
    for(int j = 1; j < stacks; j++) {
        for(int k = 0; k < slices; k++) {
            A = {j * r * sin(k * angle), height - float(j) * (height / float(stacks)), j * r * cos(k * angle)};
            B = {j * r * sin((k + 1) * angle), height - float(j) * (height / float(stacks)),
                 j * r * cos((k + 1) * angle)};
            C = {(j + 1) * r * sin(k * angle), height - float(j + 1) * (height / float(stacks)),
                 (j + 1) * r * cos(k * angle)};
            D = {(j + 1) * r * sin((k + 1) * angle), height - float(j + 1) * (height / float(stacks)),
                 (j + 1) * r * cos((k + 1) * angle)};

            AB = {B[0] - A[0], B[1] - A[1], B[2] - A[2]};
            AC = {C[0] - A[0], C[1] - A[1], C[2] - A[2]};
            DB = {B[0] - D[0], B[1] - D[1], B[2] - D[2]};
            DC = {C[0] - D[0], C[1] - D[1], C[2] - D[2]};

            AddVertex(B,
                      glm::normalize(glm::cross(-AB, -DB)),
                      {(float(k + 1) / float(slices)),
                       textureConeBodyOffsetY + (float(j) / float(stacks)) * (1 - textureConeBodyOffsetY)});
            AddVertex(A,
                      glm::normalize(glm::cross(AC, AB)),
                      {(float(k) / float(slices)),
                       textureConeBodyOffsetY + (float(j) / float(stacks)) * (1 - textureConeBodyOffsetY)});
            AddVertex(C,
                      glm::normalize(glm::cross(-DC, -AC)),
                      {(float(k) / float(slices)),
                       textureConeBodyOffsetY + (float(j + 1) / float(stacks)) * (1 - textureConeBodyOffsetY)});

            AddVertex(C,
                      glm::normalize(glm::cross(-DC, -AC)),
                      {(float(k) / float(slices)),
                       textureConeBodyOffsetY + (float(j + 1) / float(stacks)) * (1 - textureConeBodyOffsetY)});
            AddVertex(D,
                      glm::normalize(glm::cross(DB, DC)),
                      {(float(k + 1) / float(slices)),
                       textureConeBodyOffsetY + (float(j + 1) / float(stacks)) * (1 - textureConeBodyOffsetY)});
            AddVertex(B,
                      glm::normalize(glm::cross(-AB, -DB)),
                      {(float(k + 1) / float(slices)),
                       textureConeBodyOffsetY + (float(j) / float(stacks)) * (1 - textureConeBodyOffsetY)});
        }
    }


    // Draw cone tip
    for(int i = 0; i < slices; i++) {
        A = {r * sin(i * angle), height - (height / float(stacks)), r * cos(i * angle)};
        B = {r * sin((i + 1) * angle), height - (height / float(stacks)), r * cos((i + 1) * angle)};
        C = {0.0, height, 0.0};

        AB = {B[0] - A[0], B[1] - A[1], B[2] - A[2]};
        AC = {C[0] - A[0], C[1] - A[1], C[2] - A[2]};
        BC = {C[0] - B[0], C[1] - B[1], C[2] - B[2]};

        AddVertex(C,
                  {0, 1, 0},
                  {(float(i) / float(slices)), textureConeBodyOffsetY});
        AddVertex(A,
                  glm::normalize(glm::cross(AB, AC)),
                  {(float(i) / float(slices)),
                   textureConeBodyOffsetY + (1 / float(stacks)) * (1 - textureConeBodyOffsetY)});
        AddVertex(B,
                  glm::normalize(glm::cross(BC, -AB)),
                  {(float(i + 1) / float(slices)),
                   textureConeBodyOffsetY + (1 / float(stacks)) * (1 - textureConeBodyOffsetY)});
    }
}
