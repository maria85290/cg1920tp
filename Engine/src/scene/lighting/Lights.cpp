#include <iostream>

#include "Lights.h"
#include "PointLight.h"
#include "DirectionalLight.h"

using tinyxml2::XMLNode, tinyxml2::XMLElement;

using namespace std;

namespace engine::scene::lighting {
    bool Lights::ParseXml(const XMLNode *lightsNode) {
        const XMLNode *childNode = lightsNode->FirstChild();

        while(childNode != nullptr) {
            string nodeName(childNode->Value());

            if(nodeName != "light") {
                cerr << "Encontrada uma node chamada " + nodeName + " dentro da tag lights!" << endl;
                return false;
            }

            const XMLElement *elem = childNode->ToElement();
            const string type = string(elem->Attribute("type"));

            if(type.empty()) {
                cerr << "Specified light without default type!" << endl;
                return false;
            }

            Light* light;

            if(type == "point" || type == "POINT") {
                light = new PointLight();
            } else if(type == "directional" || type == "DIRECTIONAL") {
                light = new DirectionalLight();
            } else {
                cerr << "Tipo de luz " + type + " desconhecido!" << endl;
                return false;
            }

            light->ParseXml(childNode);

            this->lights.push_back(light);

            childNode = childNode->NextSibling();
        }

        return true;
    }

    Lights::~Lights() {
        for(auto light : this->lights) {
            delete light;
        }
    }

    void Lights::Enable() const {
        for(auto light : this->lights) {
            light->Enable();
        }
    }

    void Lights::Disable() const {
        for(auto light : this->lights) {
            light->Disable();
        }
    }
}
