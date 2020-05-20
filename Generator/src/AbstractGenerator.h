#ifndef CG_TP_ABSTRACTGENERATOR_H
#define CG_TP_ABSTRACTGENERATOR_H

#include <map>
#include <list>
#include <fstream>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/vec3.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

struct vertex_data {
    glm::dvec3 pos;
    glm::dvec3 normal;
    glm::dvec2 textureCoords;

    bool operator==(const vertex_data&) const;
};

namespace std {
    template<>
    struct hash<struct vertex_data> {
        std::size_t operator()(const vertex_data&) const;
    };
}

/**
 * Um Gerador é capaz de gerar vértices para um tipo de sólido geométrico arbitrário,
 * dados certos parâmetros.
 * Um Gerador é também capaz de fazer parse dos parâmetros passados à consola, para
 * determinar as proprierdades do sólido que tem de gerar.
 * Por último, um Gerador é capaz de guardar os vértices num ficheiro, num formato comum.
 */
class AbstractGenerator {
private:
    /** @var vertices Os vértices que este gerador gerou. */
    std::unordered_map<vertex_data, unsigned short> vertices;

    /** @var indices */
    std::list<unsigned short> indices;

    /** @var nextIndex The next index to use for the next new vertex that comes along. */
    int nextIndex = 0;

    /** @var filename O nome do ficheiro onde guardar os vértices gerados. */
    std::string filename;

protected:
    void SetFilename(const std::string& filename) {
        this->filename = filename;
    }

    void AddVertex(const glm::dvec3& v, const glm::dvec3& n, const glm::dvec2& t);

    inline void AddVertex(const double& x, const double& y, const double& z,
                          const double& nx, const double& ny, const double& nz,
                          const double& tx, const double& ty) {
        this->AddVertex({x, y, z}, {nx, ny, nz}, {tx, ty});
    }

public:
    virtual ~AbstractGenerator() = default;

    const std::string& GetFilename() {
        return this->filename;
    }

    /**
     * Função que faz parse dos parâmetros passados à consola para determinar as
     * propriedades do sólido a gerar, bem como o ficheiro onde guardar o resultado.
     *
     * @param argc
     * @param argv
     * @return true em caso de sucesso, false em caso de erro
     */
    virtual bool ParseArguments(int argc, char *argv[]) = 0;

    /**
     * Função que, dadas as propriedadas anteriormente lidas da consola,
     * calcula os vértices necessários para gerar o sólido com as propriedades
     * dadas.
     */
    virtual void GenerateVertices() = 0;

    /**
     * Função que guarda a lista de vértices num formato comum, para depois
     * ser interpretado pela Engine corretamente.
     *
     * O formato é comum a todos os geradores; portanto, esta função também.
     */
    void SaveVerticesToFile();
};

#endif //CG_TP_ABSTRACTGENERATOR_H
