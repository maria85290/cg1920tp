#ifndef CG_TP_ENGINE_SRC_GLOBJECTS_MODELMESH_H_
#define CG_TP_ENGINE_SRC_GLOBJECTS_MODELMESH_H_

#include <vector>
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

        long numVertices = 0;
        GLuint vbo;
    protected:
        void AddVertex(float x, float y, float z) {
            vertices.push_back({x, y, z});
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
