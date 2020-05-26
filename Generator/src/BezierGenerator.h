#include "AbstractGenerator.h"

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <tuple>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

/**
 * Define uma estrutura de utilidade para simplificar o código relacionado com a multiplicação de matrizes.
 * Esta estrutura é, em essência, uma matriz de 16x16, ou, vista de outra forma, uma matriz de 4x4 cujos elementos
 * são pontos (dvec4), e não apenas floats simples.
 */
typedef struct vdmat4 {
    glm::dmat4 a, b, c, d;
} vdmat4;

class BezierGenerator : public AbstractGenerator {
private:
    std::string patchFilename;
    int tessellationLevel;

    std::vector<std::vector<int>> patches;
    std::vector<glm::dvec4> controlPoints;

    const std::pair<glm::dvec3, glm::dvec3> ComputePatchPoint(double u, double v,
                                       const glm::dvec4& p00, const glm::dvec4& p01, const glm::dvec4& p02, const glm::dvec4& p03,
                                       const glm::dvec4& p10, const glm::dvec4& p11, const glm::dvec4& p12, const glm::dvec4& p13,
                                       const glm::dvec4& p20, const glm::dvec4& p21, const glm::dvec4& p22, const glm::dvec4& p23,
                                       const glm::dvec4& p30, const glm::dvec4& p31, const glm::dvec4& p32, const glm::dvec4& p33
    ) const;

    inline const std::pair<glm::dvec3, glm::dvec3> ComputePatchPoint(const std::vector<int>& patch,
                                                                     double u,
                                                                     double v) const {
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
 * Define a multiplicação entre um dvector com 4 componentes e uma matriz 4x4 de vetores com 4 componentes cada.
 *
 * Esta operação está definida como:
 * - O resultado é uma matriz 4x4 de floats;
 * - Cada linha da matriz resultante é o resultado da operação v * m[i].
 *
 * @param v O vetor a multiplicar
 * @param m A matriz a multiplicar
 */
inline glm::dmat4 operator*(const glm::dvec4& v, const vdmat4& m) {
    return { v * m.a, v * m.b, v * m.c, v * m.d };
}

/**
 * Define a transposta de uma matriz 4x4 de vetores com 4 componentes cada.
 *
 * Esta operação está definida como sendo a simples transposição das matrizes 4x4 constituintes.
 *
 * @param m A matriz a transpor
 */
inline vdmat4 transposeEach(const vdmat4& m) {
    return { glm::transpose(m.a), glm::transpose(m.b), glm::transpose(m.c), glm::transpose(m.d) };
}
