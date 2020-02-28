#ifndef CG_TP_GENERATOR_SRC_SPHEREGENERATOR_H_
#define CG_TP_GENERATOR_SRC_SPHEREGENERATOR_H_

#include "AbstractGenerator.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <list>

#include <Common/vectors.h>
#include <math.h>
#include <string>
#include <stdbool.h> 


class SphereGenerator : public AbstractGenerator {
private:
    int radius_;
    int slices_;
    int stacks_;

public:
    ~SphereGenerator() override = default;

    bool ParseArguments(int argc, char *argv[]) override;

    void GenerateVertices() override;
};

#endif //CG_TP_GENERATOR_SRC_SPHEREGENERATOR_H_

