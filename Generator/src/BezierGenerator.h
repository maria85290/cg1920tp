
#include "AbstractGenerator.h"

#include <list>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

class    BezierGenerator : public AbstractGenerator {
private:
    string file_read;
    int tesselation;

public:

    ~BezierGenerator() override = default;

    bool ParseArguments(int argc, char* argv[]) override;

    void GenerateVertices() override;
};

