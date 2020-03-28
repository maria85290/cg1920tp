#ifndef CG_TP_ENGINE_SRC_GROUP_H_
#define CG_TP_ENGINE_SRC_GROUP_H_

#include <vector>

#include "Model.h"
#include "Entity.h"

namespace engine::entities {
    class Group: public Entity {
    private:
        std::vector<const Entity*> entities = std::vector<const Entity*>();

        void AddEntity(const Entity *entity) {
            entities.push_back(entity);
        }

    public:
        ~Group() override;

        bool ParseXml(tinyxml2::XMLNode *groupNode) override;
        void Render() const override;
    };
}

#endif //CG_TP_ENGINE_SRC_GROUP_H_
