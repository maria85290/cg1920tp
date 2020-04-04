#ifndef CG_TP_PLANEGENERATOR_H
#define CG_TP_PLANEGENERATOR_H

#include "AbstractGenerator.h"

#include <list>
#include <string>

#include <glm/vec3.hpp>

class PlaneGenerator : public AbstractGenerator {
private:
    int plane = 0;
    int width = 0;
    int height = 0;

    static const int kPlaneXY = 0;
    static const int kPlaneYX = 1;
    static const int kPlaneXZ = 2;
    static const int kPlaneZX = 3;
    static const int kPlaneYZ = 4;
    static const int kPlaneZY = 5;


public:
    ~PlaneGenerator() override = default;

    bool ParseArguments(int argc, char *argv[]) override;

    void GenerateVertices() override;
};

#endif //CG_TP_PLANEGENERATOR_H
