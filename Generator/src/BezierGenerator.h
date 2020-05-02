#include "AbstractGenerator.h"

#include <iostream>
#include <fstream>
#include <string>
#include <list>

#define _USE_MATH_DEFINES
#include <math.h>

class BezierGenerator : public AbstractGenerator {
private:
    std::string patchFilename;
    int tessellationLevel;

    std::vector<std::vector<int>> patches;
    std::vector<glm::vec4> controlPoints;

//    const glm::vec3 ComputeCurvePoint(float t, const glm::vec3& p1, const glm::vec3& p2,
//                                      const glm::vec3& p3, const glm::vec3& p4);

    const glm::vec3 ComputePatchPoint(float u, float v,
                                                       const glm::vec3& p00, const glm::vec3& p01, const glm::vec3& p02, const glm::vec3& p03,
                                                       const glm::vec3& p10, const glm::vec3& p11, const glm::vec3& p12, const glm::vec3& p13,
                                                       const glm::vec3& p20, const glm::vec3& p21, const glm::vec3& p22, const glm::vec3& p23,
                                                       const glm::vec3& p30, const glm::vec3& p31, const glm::vec3& p32, const glm::vec3& p33
    );

    const glm::vec3 ComputePatchPoint(float u, float v, const std::vector<int>& patch);

public:

    ~BezierGenerator() override = default;

    bool ParseArguments(int argc, char* argv[]) override;

    void GenerateVertices() override;
};
