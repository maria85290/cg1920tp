#ifndef CG_TP_ENGINE_SRC_SCENE_H_
#define CG_TP_ENGINE_SRC_SCENE_H_

#include <tinyxml2/tinyxml2.h>

#include "entities/Group.h"

namespace engine {
    class Scene {
    private:
        std::vector<const entities::Group*> groups = std::vector<const entities::Group*>();

        void AddGroup(const entities::Group* group) {
            groups.push_back(group);
        }

    public:
        ~Scene();

        bool ParseXml(tinyxml2::XMLNode* sceneNode);

        void InitGLSettings() const;

        void ClearPreviousFrame() const;
        void Render() const;
    };
}

#endif //CG_TP_ENGINE_SRC_SCENE_H_
