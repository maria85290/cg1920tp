#include "Scene.h"

#include <iostream>
#include "entities/Group.h"

using std::cout, std::cerr, std::endl;
using tinyxml2::XMLNode, tinyxml2::XMLComment;
using engine::scene::entities::Group;
using engine::scene::lighting::Lights;

namespace engine::scene {
    Scene::~Scene() {
        delete lights;

        for(auto group : this->groups) {
            delete group;
        }
    }

    bool Scene::ParseXml(const XMLNode* sceneNode) {
        if(sceneNode->NoChildren()) {
            cout << "Não contêm children." << endl;
            return false;
        }

        const XMLNode* node = sceneNode->FirstChild();

        while(node != nullptr) {
        	if(dynamic_cast<const XMLComment*>(node)) {
                node = node->NextSibling();
                continue;
            }

        	if(strcmp("lights", node->Value()) == 0) {
        	    if(this->lights != nullptr) {
        	        cerr << "Encontrado mais do que um grupo de luzes na cena!" << endl;
        	        return false;
        	    }

        	    this->lights = new Lights;
                this->lights->ParseXml(node);
            } else if(strcmp("group", node->Value()) == 0) {
                Group* group = new Group(*this);

                if(!group->ParseXml(node)) {
                    cerr << "Falha ao processar o XML do grupo!" << endl;
                    return false;
                }

                this->AddGroup(group);
            } else {
                cerr << "Encontrada tag inválida: scene->" << node->Value() << endl;
                return false;
            }

            node = node->NextSibling();
        }

        return true;
    }

    void Scene::InitGLSettings() const {
        glEnable(GL_DEPTH_TEST);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glEnable(GL_NORMALIZE);
    }

    void Scene::ClearPreviousFrame() const {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Scene::Update(double deltaTime) {
        for(auto group : this->groups) {
            group->Update(deltaTime);
        }
    }

    void Scene::Render() const {
        this->EnableLights();

        for(auto group : this->groups) {
            group->Render();
        }

        this->DisableLights();
    }

    void Scene::EnableLights() const {
        if(this->lights != nullptr) {
            glEnable(GL_LIGHTING);
            this->lights->Enable();
        }
    }

    void Scene::DisableLights() const {
        if(this->lights != nullptr) {
            this->lights->Disable();
            glDisable(GL_LIGHTING);
        }
    }
}
