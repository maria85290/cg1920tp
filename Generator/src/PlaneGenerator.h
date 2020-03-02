#ifndef CG_TP_PLANEGENERATOR_H
#define CG_TP_PLANEGENERATOR_H

#include <list>
#include <string>

#include <Common/vectors.h>

#include "AbstractGenerator.h"

class PlaneGenerator : public AbstractGenerator {
private:
    int plane_ = 0;
    int width_ = 0;
    int height_ = 0;

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
