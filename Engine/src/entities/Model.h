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

        GLdouble diffR, diffG, diffB;

        GLuint vbo;
        bool isCachedModel = false;
    protected:
        void AddVertex(double x, double y, double z) {
            vertices->push_back({x, y, z});
        }

        void GenVBOs();
    public:
        explicit Model(const Model& model, const double diffR, const double diffG, const double diffB);
        explicit Model(const std::string& filename, const double diffR, const double diffG, const double diffB);
        ~Model();

        void Render() const;

        static const Model* LoadModel(const tinyxml2::XMLElement* element);
    };
}

#endif //CG_TP_ENGINE_SRC_MODEL_H_
