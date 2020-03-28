#ifndef CG_TP_ENGINE_SRC_MODEL_H_
#define CG_TP_ENGINE_SRC_MODEL_H_

#include <string>
#include <vector>
#include <map>

#include <Common/vectors.h>

#include "../glut.h"

namespace engine::entities {
    class Model {
    private:
        static std::map<std::string, const Model*> loadedModels;

        std::string filename;
        std::vector<vec3> vertices;

        GLuint vbo;
        bool isVboOwned = false;
    protected:
        void AddVertex(double x, double y, double z) {
            vertices.push_back({x, y, z});
        }

    public:
        Model(const Model& model);
        explicit Model(const std::string& filename);

        void Render() const;

        static const Model* LoadModel(const std::string& filename);
    };
}

#endif //CG_TP_ENGINE_SRC_MODEL_H_
