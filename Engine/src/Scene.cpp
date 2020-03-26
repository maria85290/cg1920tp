#include <iostream>

#include "Scene.h"

using namespace std;

namespace engine {
  Scene::~Scene() {
      for(const Group* group : this->groups_) {
          delete group;
      }
  }

  bool Scene::ParseXml(XMLNode *sceneNode) {
      if(sceneNode->NoChildren()) {
          cout << "Não contêm children." << endl;
          return false;
      }

      XMLNode *groupNode = sceneNode->FirstChild();

      while(groupNode != nullptr) {
          if(strcmp("group", groupNode->Value()) != 0) {
              cerr << "Encontrada tag inválida: scene->" << groupNode->Value() << endl;
              return false;
          }

          Group *group = new Group;
          group->ParseXml(groupNode);

          this->AddGroup(group);

          groupNode = groupNode->NextSibling();
      }

      return true;
  }

  void Scene::Render() const {
      for(const Group *group : this->groups_) {
          group->Render();
      }
  }
}
