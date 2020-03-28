#include "../glut.h"

#include "Translate.h"

using std::cerr, std::endl;
using tinyxml2::XMLNode, tinyxml2::XMLElement, tinyxml2::XML_SUCCESS;

namespace engine::entities {
    bool Translate::ParseXml(XMLNode *translateNode) {
        const XMLElement *elem = translateNode->ToElement();

        if(elem->QueryAttribute("X", &this->vector.x) != XML_SUCCESS) {
            cerr << "[Translate] Erro: Não foi encontrado o atributo axisX." << endl;
            return false;
        }

        if(elem->QueryAttribute("Y", &this->vector.y) != XML_SUCCESS) {
            cerr << "[Translate] Erro: Não foi encontrado o atributo axisY." << endl;
            return false;
        }

        if(elem->QueryAttribute("Z", &this->vector.z) != XML_SUCCESS) {
            cerr << "[Translate] Erro: Não foi encontrado o atributo axisZ." << endl;
            return false;
        }

        return true;
    }

    void Translate::Render() const {
        glTranslated(this->vector.x, this->vector.y, this->vector.z);
    }
}
