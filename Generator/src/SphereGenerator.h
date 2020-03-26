#ifndef CG_TP_GENERATOR_SRC_SPHEREGENERATOR_H_
#define CG_TP_GENERATOR_SRC_SPHEREGENERATOR_H_

#define _USE_MATH_DEFINES
#include <math.h>

#include <list>
#include <string>

#include <Common/vectors.h>

#include "AbstractGenerator.h"

class SphereGenerator : public AbstractGenerator {
private:
    int radius;
    int slices;
    int stacks;

public:
    ~SphereGenerator() override = default;

    bool ParseArguments(int argc, char *argv[]) override;

    void GenerateVertices() override;
};

#endif //CG_TP_GENERATOR_SRC_SPHEREGENERATOR_H_

