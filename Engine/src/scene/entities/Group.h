#ifndef CG_TP_ENGINE_SRC_GROUP_H_
#define CG_TP_ENGINE_SRC_GROUP_H_

#include <vector>

#include "Model.h"
#include "Entity.h"

namespace engine::scene::entities {
    class Group: public Entity {
    private:
        std::vector<Entity*> entities;

        void AddEntity(Entity *entity) {
            entities.push_back(entity);
        }

    public:
        ~Group() override;

        bool ParseXml(const tinyxml2::XMLNode *groupNode) override;
        void Render() const override;
    };
}

#endif //CG_TP_ENGINE_SRC_GROUP_H_
