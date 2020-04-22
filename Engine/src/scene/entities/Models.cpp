#include <iostream>

#include "Model.h"

#include "Models.h"

using std::cerr, std::endl;
using tinyxml2::XMLNode, tinyxml2::XMLElement, tinyxml2::XMLComment;

namespace engine::scene::entities {
    bool Models::ParseXml(const XMLNode *modelsNode) {
        const XMLNode *node = modelsNode->FirstChild();

        while(node != nullptr) {
            if(dynamic_cast<const XMLComment*>(node)) {
                node = node->NextSibling();
                continue;
            }

            const XMLElement *element = node->ToElement();

            if(strcmp("model", node->Value()) != 0) {
                cerr << "Esperado valor 'model', obtido '" << node->Value() << "'" << endl;
                return false;
            }

            Model* model = new Model(element);

            if(model == nullptr) {
                return false;
            }

            this->AddModel(model);

            node = node->NextSibling();
        }

        return true;
    }

    Models::~Models() {
        for(auto model : this->models) {
            delete model;
        }
    }

    void Models::Render() const {
        for(auto model : models) {
            model->Render();
        }
    }
}
