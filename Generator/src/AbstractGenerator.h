#ifndef CG_TP_ABSTRACTGENERATOR_H
#define CG_TP_ABSTRACTGENERATOR_H

#include <list>
#include <fstream>

#include <glm/vec3.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

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
    std::list<glm::vec3> vertices = std::list<glm::vec3>();

    /** @var filename O nome do ficheiro onde guardar os vértices gerados. */
    std::string filename;

protected:
    void SetFilename(const std::string& filename) {
        this->filename = filename;
    }

    void AddVertex(const glm::vec3& vertex) {
        this->vertices.push_back(vertex);
    }

    void AddVertex(const double& x, const double& y, const double& z) {
        this->vertices.emplace_back(x, y, z);
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
    void SaveVerticesToFile() {
        std::ofstream file(filename);

        for(const glm::vec3& vertex : vertices) {
            file << vertex.x << " "
                 << vertex.y << " "
                 << vertex.z << std::endl;
        }

        file.close();
    }
};

#endif //CG_TP_ABSTRACTGENERATOR_H
