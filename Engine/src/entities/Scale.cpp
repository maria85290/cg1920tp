#include "Scale.h"

namespace engine::entities {
    bool Scale::ParseXml(XMLNode *translateNode) {
        const XMLElement *elem = translateNode->ToElement();

        if(elem->QueryAttribute("X", &this->factors_.x) != XML_SUCCESS) {
            cerr << "[Scale] Erro: Não foi encontrado o atributo axisX." << endl;
            return false;
        }

        if(elem->QueryAttribute("Y", &this->factors_.y) != XML_SUCCESS) {
            cerr << "[Scale] Erro: Não foi encontrado o atributo axisY." << endl;
            return false;
        }

        if(elem->QueryAttribute("Z", &this->factors_.z) != XML_SUCCESS) {
            cerr << "[Scale] Erro: Não foi encontrado o atributo axisZ." << endl;
            return false;
        }

        return true;
    }

    void Scale::Render() const {
        glScaled(this->factors_.x, this->factors_.y, this->factors_.z);
    }
}
