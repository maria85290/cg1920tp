#ifndef CG_TP_ENGINE_SRC_SCENE_H_
#define CG_TP_ENGINE_SRC_SCENE_H_

#include <tinyxml2/tinyxml2.h>

#include "entities/Group.h"

using namespace tinyxml2;
using namespace engine::entities;

namespace engine {
    class Scene {
    private:
        vector<const Group*> groups = vector<const Group*>();

        void AddGroup(const Group* group) {
            groups.push_back(group);
        }

    public:
        ~Scene();

        bool ParseXml(XMLNode* sceneNode);
        void Render() const;
    };
}

#endif //CG_TP_ENGINE_SRC_SCENE_H_
