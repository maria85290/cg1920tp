#include <glm/gtc/type_ptr.hpp>

#include "SpotLight.h"

namespace engine::scene::lighting {

    bool SpotLight::ParseXml(const tinyxml2::XMLNode *lightNode) {
        if(!PointLight::ParseXml(lightNode)) {
            return false;
        }

        auto elem = lightNode->ToElement();

        this->direction.x = elem->FloatAttribute("dirX", 0.0f);
        this->direction.y = elem->FloatAttribute("dirY", 0.0f);
        this->direction.z = elem->FloatAttribute("dirZ", 0.0f);

        this->cutoffAngle = elem->FloatAttribute("cutoffAngle", 45.0f);
        this->cutoffExponent = elem->FloatAttribute("cutoffExponent", 0.0f);

        this->attenuationConstant = elem->FloatAttribute("attenuationConstant", 1.0f);
        this->attenuationLinear = elem->FloatAttribute("attenuationLinear", 0.0f);
        this->attenuationQuadratic = elem->FloatAttribute("attenuationQuadratic", 0.0f);

        return true;
    }

    void SpotLight::Enable() const {
        PointLight::Enable();

        glLightfv(GetLightNo(), GL_SPOT_DIRECTION, glm::value_ptr(this->direction));

        glLightf(GetLightNo(), GL_SPOT_EXPONENT, this->cutoffExponent);
        glLightf(GetLightNo(), GL_SPOT_CUTOFF, this->cutoffAngle);

        glLightf(GetLightNo(), GL_CONSTANT_ATTENUATION, this->attenuationConstant);
        glLightf(GetLightNo(), GL_LINEAR_ATTENUATION, this->attenuationLinear);
        glLightf(GetLightNo(), GL_QUADRATIC_ATTENUATION, this->attenuationQuadratic);
    }
}
