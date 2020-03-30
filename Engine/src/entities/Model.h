#ifndef CG_TP_ENGINE_SRC_MODEL_H_
#define CG_TP_ENGINE_SRC_MODEL_H_

#include <string>
#include <vector>
#include <map>
#include <tinyxml2/tinyxml2.h>

#include <Common/vectors.h>

#include "../glut.h"

namespace engine::entities {
    class Model {
    private:
        static std::map<std::string, const Model*> loadedModels;

        std::string filename;
        std::vector<vec3>* vertices;

        GLubyte diffR, diffG, diffB;

        GLuint vbo;
        bool isCachedModel = false;
    protected:
        void AddVertex(double x, double y, double z) {
            vertices->push_back({x, y, z});
        }

        void GenVBOs();
    public:
        explicit Model(const Model& model, const int diffR, const int diffG, const int diffB);
        explicit Model(const std::string& filename, const int diffR, const int diffG, const int diffB);
        ~Model();

        void Render() const;

        static const Model* LoadModel(const tinyxml2::XMLElement* element);
    };
}

#endif //CG_TP_ENGINE_SRC_MODEL_H_
