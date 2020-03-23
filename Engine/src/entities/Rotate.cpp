#include "Rotate.h"

namespace entities {
    bool Rotate::ParseXml(XMLNode *rotateNode) {
        const XMLElement *elem = rotateNode->ToElement();

        if(elem->QueryAttribute("angle", &this->angle_) != XML_SUCCESS) {
            cerr << "[Rotate] Erro: Não foi encontrado o atributo angle." << endl;
            return false;
        }

        if(elem->QueryAttribute("axisX", &this->vector_.x) != XML_SUCCESS) {
            cerr << "[Rotate] Erro: Não foi encontrado o atributo axisX." << endl;
            return false;
        }

        if(elem->QueryAttribute("axisY", &this->vector_.y) != XML_SUCCESS) {
            cerr << "[Rotate] Erro: Não foi encontrado o atributo axisY." << endl;
            return false;
        }

        if(elem->QueryAttribute("axisZ", &this->vector_.z) != XML_SUCCESS) {
            cerr << "[Rotate] Erro: Não foi encontrado o atributo axisZ." << endl;
            return false;
        }

        // Sem erros!
        return true;
    }

    void Rotate::Render() const {
        glRotated(angle_, vector_.x, vector_.y, vector_.z);
    }
}
