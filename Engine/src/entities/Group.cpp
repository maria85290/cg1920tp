#include <iostream>

#include "Models.h"
#include "Translate.h"
#include "Rotate.h"
#include "Scale.h"

#include "Group.h"

namespace engine::entities {
    Group::~Group() {
        for(const Entity *entity : this->entities) {
            delete entity;
        }
    }

    bool Group::ParseXml(XMLNode *groupNode) {
        XMLNode *childNode = groupNode->FirstChild();

        while(childNode != nullptr) {
            string nodeName(childNode->Value());

            Entity *entity;

            if(nodeName == "translate") {
                entity = new Translate;
            } else if(nodeName == "rotate") {
                entity = new Rotate;
            } else if(nodeName == "scale") {
                entity = new Scale;
            } else if(nodeName == "models") {
                entity = new Models;
            } else if(nodeName == "group") {
                entity = new Group;
            } else {
                cerr << "Errou!" << endl; // TODO
                return false;
            }

            entity->ParseXml(childNode);
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
