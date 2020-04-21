#include <iostream>

#include "Models.h"
#include "Translate.h"
#include "Rotate.h"
#include "Scale.h"

#include "Group.h"

using std::string, std::cerr, std::endl;
using tinyxml2::XMLNode, tinyxml2::XMLComment;

namespace engine::scene::entities {
    Group::~Group() {
        for(const Entity *entity : this->entities) {
            delete entity;
        }
    }

    bool Group::ParseXml(const XMLNode *groupNode) {
        const XMLNode *childNode = groupNode->FirstChild();

        bool translate = false, scale = false, rotate = false, models = false;

        while(childNode != nullptr) {
            string nodeName(childNode->Value());

            Entity *entity;

            if(nodeName == "translate") {
                if(translate) {
                    cerr << "Encontradas duas tags translate dentro do mesmo grupo!" << endl;
                    return false;
                }

                entity = new Translate;
                translate = true;
            } else if(nodeName == "rotate") {
                if(rotate) {
                    cerr << "Encontradas duas tags rotate dentro do mesmo grupo!" << endl;
                    return false;
                }

                entity = new Rotate;
                rotate = true;
            } else if(nodeName == "scale") {
                if(scale) {
                    cerr << "Encontradas duas tags scale dentro do mesmo grupo!" << endl;
                    return false;
                }

                entity = new Scale;
                scale = true;
            } else if(nodeName == "models") {
                if(models) {
                    cerr << "Encontradas duas tags models dentro do mesmo grupo!" << endl;
                    return false;
                }

                entity = new Models;
                models = true;
            } else if(nodeName == "group") {
                entity = new Group;
            } else if(dynamic_cast<const XMLComment*>(childNode)) {
                childNode = childNode->NextSibling();
                continue;
            } else {
                cerr << "Erro: A node " << nodeName << " foi encontrada dentro de um grupo, mas esta node não é reconhecida!" << endl;
                return false;
            }

            if(!entity->ParseXml(childNode)) {
                return false;
            }

            this->AddEntity(entity);

            childNode = childNode->NextSibling();
        }

        return true;
    }

    void Group::Render() const {
        glPushMatrix();

        for(const Entity *entity : this->entities) {
            entity->Render();
        }

        glPopMatrix();
    }
}
