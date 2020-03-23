#include <iostream>
#include "../glut.h"

#include "Group.h"
#include "Models.h"

namespace entities {
    Group::~Group() {
        for(const Entity *entity : this->entities_) {
            delete entity;
        }
    }

    bool Group::ParseXml(XMLNode *groupNode) {
        XMLNode *childNode = groupNode->FirstChild();

        while(childNode != nullptr) {
            if(strcmp("translate", childNode->Value()) == 0) {
                // TODO
            } else if(strcmp("rotate", childNode->Value()) == 0) {
                // TODO
            } else if(strcmp("scale", childNode->Value()) == 0) {
                // TODO
            } else if(strcmp("models", childNode->Value()) == 0) {
                auto *models = new Models;
                models->ParseXml(childNode);

                this->AddEntity(models);
            } else if(strcmp("group", childNode->Value()) == 0) {
                auto *group = new Group;
                group->ParseXml(childNode);

                this->AddEntity(group);
            } else {
                cerr << "Errou!" << endl; // TODO
                return false;
            }

            childNode = childNode->NextSibling();
        }

        return true;
    }

    void Group::Render() const {
        glPushMatrix();

        for(const Entity *entity : this->entities_) {
            entity->Render();
        }

        glPopMatrix();
    }
}
