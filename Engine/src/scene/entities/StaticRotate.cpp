#include <glad/glad.h>

#include "StaticRotate.h"

using std::cerr, std::endl;
using tinyxml2::XMLNode, tinyxml2::XMLElement, tinyxml2::XML_SUCCESS;

namespace engine::scene::entities {
    bool StaticRotate::ParseXml(const XMLNode *rotateNode) {
        const XMLElement *elem = rotateNode->ToElement();

        if(elem->QueryAttribute("angle", &this->angle) != XML_SUCCESS) {
            cerr << "[Rotate] Erro: Não foi encontrado o atributo angle." << endl;
            return false;
        }

        if(elem->QueryAttribute("axisX", &this->vector.x) != XML_SUCCESS) {
            cerr << "[Rotate] Erro: Não foi encontrado o atributo axisX." << endl;
            return false;
        }

        if(elem->QueryAttribute("axisY", &this->vector.y) != XML_SUCCESS) {
            cerr << "[Rotate] Erro: Não foi encontrado o atributo axisY." << endl;
            return false;
        }

        if(elem->QueryAttribute("axisZ", &this->vector.z) != XML_SUCCESS) {
            cerr << "[Rotate] Erro: Não foi encontrado o atributo axisZ." << endl;
            return false;
        }

        // Sem erros!
        return true;
    }

    void StaticRotate::Render() const {
        glRotatef(angle, vector.x, vector.y, vector.z);
    }
}
