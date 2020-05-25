#ifndef CG_TP_ENGINE_SRC_ENTITIES_ROTATE_H_
#define CG_TP_ENGINE_SRC_ENTITIES_ROTATE_H_

#include <glm/vec3.hpp>
#include "Entity.h"

namespace engine::scene::entities {
    class StaticRotate: public Entity {
    private:
        /** The rotation angle, in degrees. */
        float angle;
        /** The rotation vector. */
        glm::vec3 vector;

    public:
        StaticRotate(const Scene& scene): Entity(scene) {}
        ~StaticRotate() override = default;

        bool ParseXml(const tinyxml2::XMLNode *rotateNode) override;
        void Render() const override;
    };
}

#endif //CG_TP_ENGINE_SRC_ENTITIES_ROTATE_H_
