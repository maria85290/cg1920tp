#include "DirectionalLight.h"

namespace engine::scene::lighting {
    bool DirectionalLight::ParseXml(const tinyxml2::XMLNode *lightNode) {
        if(!PointLight::ParseXml(lightNode)) {
            return false;
        }

        // Directional lights only have a different w component from positional lights
        this->position.w = 0.0f;

        return true;
    }
}
