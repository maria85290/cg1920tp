#include "Light.h"

using std::string;

namespace engine::scene::lighting {
    int Light::NEXT_LIGHT_NO = GL_LIGHT0;

    glm::vec4 Light::ParseLightComponent(const string& prefix, const tinyxml2::XMLElement* element, const glm::vec4& def) {
        glm::vec4 component(1.0f);

        component.r = element->FloatAttribute((prefix + "R").c_str(), def.r * 255) / 255;
        component.g = element->FloatAttribute((prefix + "G").c_str(), def.g * 255) / 255;
        component.b = element->FloatAttribute((prefix + "B").c_str(), def.b * 255) / 255;
        component.a = element->FloatAttribute((prefix + "A").c_str(), def.a * 255) / 255;

        return component;
    }
}
