#ifndef CG_TP_GENERATOR_SRC_CONEGENERATOR_H_
#define CG_TP_GENERATOR_SRC_CONEGENERATOR_H_

#include "AbstractGenerator.h"
#include <string>


class ConeGenerator : public AbstractGenerator {
private:
    int bottomRadius;
    int height;
    int slices;
    int stacks;

public:
    ~ConeGenerator() override = default;

    bool ParseArguments(int argc, char *argv[]) override;

    void GenerateVertices() override;
};

#endif //CG_TP_GENERATOR_SRC_CONEGENERATOR_H_
