#include "AbstractGenerator.h"

#include <iostream>
#include <fstream>
#include <string>
#include <list>

#define _USE_MATH_DEFINES
#include <math.h>

/**
 * Define uma estrutura de utilidade para simplificar o código relacionado com a multiplicação de matrizes.
 * Esta estrutura é, em essência, uma matriz de 16x16, ou, vista de outra forma, uma matriz de 4x4 cujos elementos
 * são pontos (vec4), e não apenas floats simples.
 */
typedef struct vmat4 {
    glm::mat4 a, b, c, d;
} vmat4;

class BezierGenerator : public AbstractGenerator {
private:
    std::string patchFilename;
    int tessellationLevel;

    std::vector<std::vector<int>> patches;
    std::vector<glm::vec4> controlPoints;

    const glm::vec4 ComputePatchPoint(float u, float v,
                                       const glm::vec4& p00, const glm::vec4& p01, const glm::vec4& p02, const glm::vec4& p03,
                                       const glm::vec4& p10, const glm::vec4& p11, const glm::vec4& p12, const glm::vec4& p13,
                                       const glm::vec4& p20, const glm::vec4& p21, const glm::vec4& p22, const glm::vec4& p23,
                                       const glm::vec4& p30, const glm::vec4& p31, const glm::vec4& p32, const glm::vec4& p33
    ) const;

    inline const glm::vec4 ComputePatchPoint(float u, float v, const std::vector<int>& patch) const {
        return this->ComputePatchPoint(
            u, v,
            controlPoints[patch[0]], controlPoints[patch[1]], controlPoints[patch[2]], controlPoints[patch[3]],
            controlPoints[patch[4]], controlPoints[patch[5]], controlPoints[patch[6]], controlPoints[patch[7]],
            controlPoints[patch[8]], controlPoints[patch[9]], controlPoints[patch[10]], controlPoints[patch[11]],
            controlPoints[patch[12]], controlPoints[patch[13]], controlPoints[patch[14]], controlPoints[patch[15]]
        );
    }

public:

    ~BezierGenerator() override = default;

    bool ParseArguments(int argc, char* argv[]) override;

    void GenerateVertices() override;
};

/**
 * Define a multiplicação entre um vector com 4 componentes e uma matriz 4x4 de vetores com 4 componentes cada.
 *
 * Esta operação está definida como:
 * - O resultado é uma matriz 4x4 de floats;
 * - Cada linha da matriz resultante é o resultado da operação v * m[i].
 *
 * @param v O vetor a multiplicar
 * @param m A matriz a multiplicar
 */
inline glm::mat4 operator*(const glm::vec4& v, const vmat4& m) {
    return {v * m.a, v * m.b, v * m.c, v * m.d };
}

/**
 * Define a transposta de uma matriz 4x4 de vetores com 4 componentes cada.
 *
 * Esta operação está definida como sendo a simples transposição das matrizes 4x4 constituintes.
 *
 * @param m A matriz a transpor
 */
inline vmat4 transpose(const vmat4& m) {
    return { glm::transpose(m.a), glm::transpose(m.b), glm::transpose(m.c), glm::transpose(m.d) };
}
