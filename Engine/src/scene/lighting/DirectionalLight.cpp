#include "DirectionalLight.h"

namespace engine::scene::lighting {
    bool DirectionalLight::ParseXml(const tinyxml2::XMLNode *lightNode) {
        if(!PointLight::ParseXml(lightNode)) {
            return false;
        }

        auto elem = lightNode->ToElement();

        this->position.x = elem->FloatAttribute("dirX", 0.0f);
        this->position.y = elem->FloatAttribute("dirY", 0.0f);
        this->position.z = elem->FloatAttribute("dirZ", 0.0f);
        this->position.w = 0.0f; // Directional lights only have a different w component from positional lights

        return true;
    }
}
