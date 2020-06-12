#include "PointLight.h"

namespace engine::scene::lighting {
    bool PointLight::ParseXml(const tinyxml2::XMLNode* lightNode) {
        auto elem = lightNode->ToElement();

        this->position.x = elem->FloatAttribute("posX", 0.0f);
        this->position.y = elem->FloatAttribute("posY", 0.0f);
        this->position.z = elem->FloatAttribute("posZ", 0.0f);
        this->position.w = 1.0f; // Point lights have w = 1

        this->ambient  = Light::ParseLightComponent("amb", elem, {0.2, 0.2, 0.2, 1.0});
        this->diffuse  = Light::ParseLightComponent("diff", elem, {0.8, 0.8, 0.8, 1.0});
        this->specular = Light::ParseLightComponent("spec", elem, {0.0, 0.0, 0.0, 0.0});

        return true;
    }

    void PointLight::Enable() const {
        Light::Enable();

        glLightfv(GetLightNo(), GL_POSITION,  glm::value_ptr(this->position));
        glLightfv(GetLightNo(), GL_AMBIENT,   glm::value_ptr(this->ambient));
        glLightfv(GetLightNo(), GL_DIFFUSE,   glm::value_ptr(this->diffuse));
        glLightfv(GetLightNo(), GL_SPECULAR,  glm::value_ptr(this->specular));
    }
}
