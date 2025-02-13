#include <glad/glad.h>

#include "StaticTranslate.h"

using std::cerr, std::endl;
using tinyxml2::XMLNode, tinyxml2::XMLElement, tinyxml2::XML_SUCCESS;

namespace engine::scene::entities {
    bool StaticTranslate::ParseXml(const XMLNode *translateNode) {
        const XMLElement *elem = translateNode->ToElement();

        if(elem->QueryAttribute("X", &this->vector.x) != XML_SUCCESS) {
            this->vector.x = 0.0;
        }

        if(elem->QueryAttribute("Y", &this->vector.y) != XML_SUCCESS) {
            this->vector.y = 0.0;
        }

        if(elem->QueryAttribute("Z", &this->vector.z) != XML_SUCCESS) {
            this->vector.z = 0.0;
        }

        return true;
    }

    void StaticTranslate::Render() const {
        glTranslatef(this->vector.x, this->vector.y, this->vector.z);
    }
}
