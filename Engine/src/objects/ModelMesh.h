#ifndef CG_TP_ENGINE_SRC_GLOBJECTS_MODELMESH_H_
#define CG_TP_ENGINE_SRC_GLOBJECTS_MODELMESH_H_

#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glad/glad.h>

#include "ObjectCache.h"

using engine::objects::ObjectCache;

namespace engine::objects {
    /**
     * Uma ModelMesh representa um ficheiro .3d que contém um modelo 3D renderizável.
     *
     * Esta classe contém todos os métodos relacionados com a leitura de ficheiros .3d,
     * e a renderização dos modelos quando for necessário.
     *
     * Esta classe não é, no entanto,responsável por definir parâmetros que são especificados
     * na tag XML <model>, tal como a cor do objeto, a sua textura, etc. Essa responsabilidade
     * é das classes \link Model e \link Texture, respetivamente.
     *
     * Esta classe implementa também um sistema de cache: para prevenir que o mesmo modelo
     * seja carregado várias vezes e ocupe mais memória do que aquela que é necessária,
     * todas as instâncias desta classe são referenciadas apenas e só através de instâncias
     * de \code shared_ptr. Assim, sempre que é necessário carregar um modelo, a cache é
     * verificada primeiro para saber se esse modelo já foi carregado anteriormente. Se sim,
     * uma nova instância de um \code shared_ptr é criada, e é retornada essa instância.
     * Quando todos os modelos que se referem à mesma mesh forem destruidos, então a
     * instância do ModelMesh também é destruida.
     * Caso o objeto não exista já em cache, é criada uma nova instância deste objeto,
     * colocada em cache, e depois é retornado o objeto dentro de um \code shared_ptr.
     */
    class ModelMesh {
    private:
        static ObjectCache<ModelMesh> cache;

        const std::string filename;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texCoords;
        std::vector<unsigned int> indices;

        long numIndices = 0;

        GLuint vbos[4];
    protected:
        void AddVertex(const float& x, const float& y, const float& z) {
            this->vertices.emplace_back(x, y, z);
        }

        void AddNormal(const float& x, const float& y, const float& z) {
            if(x == 0 && y == 0 && z == 0)
                std::cout << "Existe uma normal que é (0, 0, 0)!" << std::endl;

            this->normals.push_back(glm::normalize(glm::vec3(x, y, z)));
        }

        void AddTexCoord(const float& x, const float& y) {
            this->texCoords.emplace_back(x, y);
        }

        void GenVBOs();
    public:
        ModelMesh(const std::string& filename);
        ModelMesh(const ModelMesh& mesh) = delete;
        ModelMesh& operator=(const ModelMesh& other) = delete;

        ~ModelMesh();

        void Render() const;

        static ObjectCache<ModelMesh>& GetCache() {
            return cache;
        }
    };
}

#endif //CG_TP_ENGINE_SRC_GLOBJECTS_MODELMESH_H_
