#include <iostream>

#include "Scene.h"

using std::cout, std::cerr, std::endl;
using tinyxml2::XMLNode;
using engine::entities::Group;

namespace engine {
    Scene::~Scene() {
        for(const Group* group : this->groups) {
            delete group;
        }
    }

    bool Scene::ParseXml(XMLNode* sceneNode) {
        if(sceneNode->NoChildren()) {
            cout << "Não contêm children." << endl;
            return false;
        }

        XMLNode* groupNode = sceneNode->FirstChild();

        while(groupNode != nullptr) {
            if(strcmp("group", groupNode->Value()) != 0) {
                cerr << "Encontrada tag inválida: scene->" << groupNode->Value() << endl;
                return false;
            }

            Group* group = new Group;
            if(!group->ParseXml(groupNode)) {
                cerr << "Falha ao processar o XML do grupo!" << endl;
                return false;
            }

            this->AddGroup(group);

            groupNode = groupNode->NextSibling();
        }

        return true;
    }

    void Scene::InitGLSettings() const {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glEnableClientState(GL_VERTEX_ARRAY);
        glPolygonMode(GL_FRONT, GL_LINE);
    }

    void Scene::ClearPreviousFrame() const {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Scene::Render() const {
        for(const Group* group : this->groups) {
            group->Render();
        }
    }
}
