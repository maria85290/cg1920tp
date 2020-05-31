#ifndef CG_TP_ENGINE_SRC_GROUP_H_
#define CG_TP_ENGINE_SRC_GROUP_H_

#include <vector>

#include "Model.h"
#include "Entity.h"

namespace engine::scene::entities {
    /**
     * Representa a tag Grupo presente nos ficheiros XML.
     *
     * Cada grupo tem, internamente, uma pipeline de renderização por si próprio.
     */
    class Group: public Entity {
    private:
        std::vector<Entity*> entities;

        void AddEntity(Entity *entity) {
            entities.push_back(entity);
        }

    public:
        Group(const Scene& scene): Entity(scene) {}
        ~Group() override;

        bool ParseXml(const tinyxml2::XMLNode *groupNode) override;
        void Update(double deltaTime) override;
        void Render() const override;
    };
}

#endif //CG_TP_ENGINE_SRC_GROUP_H_
