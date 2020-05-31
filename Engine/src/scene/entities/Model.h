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
    /**
     * Representa a tag <model> presente nos ficheiros XML.
     *
     * Cada modelo obrigatoriamente tem uma mesh, que define a sua estrutura (correspondente ao ficheiro seu .3d),
     * e pode opcionalmente ter outros parâmetros, como textura, componentes de luz, etc.
     */
    class Model {
    private:
        shared_ptr<ModelMesh> mesh;
        shared_ptr<Texture> texture;

        glm::vec4 ambientLight;
        glm::vec4 diffuseLight;
        glm::vec4 specularLight;
        glm::vec4 emissionLight;
        float shininess;

    public:
        explicit Model(const tinyxml2::XMLElement* element);

        Model(const Model& model) = delete;
        Model& operator=(const Model& other) = delete;

        ~Model() = default;

        void Render() const;
    };
}

#endif //CG_TP_ENGINE_SRC_MODEL_H_
