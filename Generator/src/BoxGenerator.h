#ifndef CG_TP_GENERATOR_SRC_BOXGENERATOR_H_
#define CG_TP_GENERATOR_SRC_BOXGENERATOR_H_

#include "AbstractGenerator.h"
#include "PlaneGenerator.h"


class BoxGenerator : public AbstractGenerator {
private:
    int dimX;
    int dimY;
    int dimZ;
   

public:
    ~BoxGenerator() override = default;
    bool ParseArguments(int argc, char *argv[]) override;
    void GenerateVertices() override;
};

#endif //CG_TP_GENERATOR_SRC_BOXGENERATOR_H_
