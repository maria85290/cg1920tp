#ifndef CG_TP_ENGINE_SRC_MODEL_H_
#define CG_TP_ENGINE_SRC_MODEL_H_

#include <string>
#include <vector>
#include <map>
#include <memory>

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <tinyxml2/tinyxml2.h>

#include "../../objects/ModelMesh.h"
#include "../../objects/Texture.h"

using std::shared_ptr;
using engine::objects::ModelMesh;
using engine::objects::Texture;

namespace engine::scene::entities {
    class Model {
    private:
        shared_ptr<ModelMesh> mesh;
        shared_ptr<Texture> texture;

        GLubyte diffR, diffG, diffB;
    public:
        explicit Model(const tinyxml2::XMLElement* element);

        Model(const Model& model) = delete;
        Model& operator=(const Model& other) = delete;

        ~Model() = default;

        void Render() const;
    };
}

#endif //CG_TP_ENGINE_SRC_MODEL_H_
