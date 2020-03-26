#ifndef CG_TP_ENGINE_SRC_GROUP_H_
#define CG_TP_ENGINE_SRC_GROUP_H_

#include <vector>

#include "Model.h"
#include "Entity.h"

using namespace std;

namespace engine::entities {
    class Group: public Entity {
    private:
        vector<const Entity*> entities = vector<const Entity*>();

        void AddEntity(const Entity *entity) {
            entities.push_back(entity);
        }

    public:
        ~Group() override;

        bool ParseXml(XMLNode *groupNode) override;
        void Render() const override;
    };
}

#endif //CG_TP_ENGINE_SRC_GROUP_H_
