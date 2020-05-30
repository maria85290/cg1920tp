#ifndef CG_TP_ENGINE_SRC_GLOBJECTS_MODELMESH_H_
#define CG_TP_ENGINE_SRC_GLOBJECTS_MODELMESH_H_

#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glad/glad.h>

#include "ObjectCache.h"

using engine::objects::ObjectCache;

namespace engine::objects {
    class ModelMesh {
    private:
        static ObjectCache<ModelMesh> cache;

        const std::string filename;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texCoords;
        std::vector<unsigned short> indices;

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
