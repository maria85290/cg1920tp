#include <glad/glad.h>

#include "TimedRotate.h"

using std::cerr, std::endl;
using tinyxml2::XMLNode, tinyxml2::XMLElement, tinyxml2::XML_SUCCESS;

namespace engine::scene::entities {
    bool TimedRotate::ParseXml(const XMLNode *rotateNode) {
        const XMLElement *elem = rotateNode->ToElement();

        if(elem->QueryAttribute("time", &this->time) != XML_SUCCESS) {
            cerr << "[Rotate] Erro: Não foi encontrado o atributo time." << endl;
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

        this->degreesPerSecond = 360.0 / double(this->time);

        // Sem erros!
        return true;
    }

    void TimedRotate::Update(double deltaTime) {
        this->angle += this->degreesPerSecond * deltaTime;
    }

    void TimedRotate::Render() const {
        glRotated(this->angle, vector.x, vector.y, vector.z);
    }
}
