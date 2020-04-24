#include <glad/glad.h>

#include "Scale.h"

using std::cerr, std::endl;
using tinyxml2::XMLNode, tinyxml2::XMLElement, tinyxml2::XML_SUCCESS;

namespace engine::scene::entities {
    bool Scale::ParseXml(const XMLNode *translateNode) {
        const XMLElement *elem = translateNode->ToElement();

        if(elem->QueryAttribute("X", &this->factors.x) != XML_SUCCESS) {
            cerr << "[Scale] Erro: Não foi encontrado o atributo axisX." << endl;
            return false;
        }

        if(elem->QueryAttribute("Y", &this->factors.y) != XML_SUCCESS) {
            cerr << "[Scale] Erro: Não foi encontrado o atributo axisY." << endl;
            return false;
        }

        if(elem->QueryAttribute("Z", &this->factors.z) != XML_SUCCESS) {
            cerr << "[Scale] Erro: Não foi encontrado o atributo axisZ." << endl;
            return false;
        }

        return true;
    }

    void Scale::Render() const {
        glScalef(this->factors.x, this->factors.y, this->factors.z);
    }
}
