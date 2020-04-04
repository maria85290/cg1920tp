#include "Scale.h"

#include <glbinding/gl/gl.h>

using std::cerr, std::endl;
using tinyxml2::XMLNode, tinyxml2::XMLElement, tinyxml2::XML_SUCCESS;

using namespace gl;

namespace engine::entities {
    bool Scale::ParseXml(XMLNode *translateNode) {
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
        glScaled(this->factors.x, this->factors.y, this->factors.z);
    }
}
