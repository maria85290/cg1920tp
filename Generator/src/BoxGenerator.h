#ifndef CG_TP_GENERATOR_SRC_BOXGENERATOR_H_
#define CG_TP_GENERATOR_SRC_BOXGENERATOR_H_

#include "AbstractGenerator.h"
#include "PlaneGenerator.h"


class BoxGenerator : public AbstractGenerator {
private:
    int dimX_;
    int dimY_;
    int dimZ_;
   

public:
    ~BoxGenerator() override = default;
    bool ParseArguments(int argc, char *argv[]) override;
    void GenerateVertices() override;
};

#endif //CG_TP_GENERATOR_SRC_BOXGENERATOR_H_
