#ifndef CG_TP_ENGINE_SRC_GLOBJECTS_MODELMESH_H_
#define CG_TP_ENGINE_SRC_GLOBJECTS_MODELMESH_H_

#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glad/glad.h>

#include "ObjectCache.h"

using engine::objects::ObjectCache;

namespace engine::objects {
    struct vertex_data {
        glm::vec3 vertexCoords;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    class ModelMesh {
    private:
        static ObjectCache<ModelMesh> cache;

        const std::string filename;
        std::vector<struct vertex_data> vertexData;
        std::vector<unsigned short> indices;

        long numIndices = 0;

        GLuint vbos[2];
    protected:
        void AddVertex(const float& x, const float& y, const float& z,
                       const float& nx, const float& ny, const float& nz,
                       const float& tx, const float& ty) {
            this->vertexData.push_back({{x, y, z}, {nx, ny, nz}, {tx, ty}});
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
