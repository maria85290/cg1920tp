#ifndef CG_TP_ABSTRACTGENERATOR_H
#define CG_TP_ABSTRACTGENERATOR_H

#include <list>

#include <Common/vectors.h>
#include <fstream>

using namespace std;

/**
 * Um Gerador é capaz de gerar vértices para um tipo de sólido geométrico arbitrário,
 * dados certos parâmetros.
 * Um Gerador é também capaz de fazer parse dos parâmetros passados à consola, para
 * determinar as proprierdades do sólido que tem de gerar.
 * Por último, um Gerador é capaz de guardar os vértices num ficheiro, num formato comum.
 */
class AbstractGenerator {
private:
    /** @var vertices_ Os vértices que este gerador gerou. */
    list<vec3> vertices_ = list<vec3>();

    /** @var filename_ O nome do ficheiro onde guardar os vértices gerados. */
    string filename_;

protected:
    void SetFilename(const string& filename) {
        this->filename_ = filename;
    }

    void AddVertex(const vec3& vertex) {
        this->vertices_.push_back(vertex);
    }

    void AddVertex(const double& x, const double& y, const double& z) {
        this->vertices_.push_back({x, y, z});
    }

public:
    virtual ~AbstractGenerator() = default;

    const string& GetFilename() {
        return this->filename_;
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
        ofstream file(filename_);

        for(const vec3& vertex : vertices_) {
            file << vertex.x << " "
                 << vertex.y << " "
                 << vertex.z << endl;
        }

        file.close();
    }
};

#endif //CG_TP_ABSTRACTGENERATOR_H
