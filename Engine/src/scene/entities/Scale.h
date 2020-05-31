#ifndef CG_TP_ENGINE_SRC_ENTITIES_SCALE_H_
#define CG_TP_ENGINE_SRC_ENTITIES_SCALE_H_

#include <glm/vec3.hpp>

#include "Entity.h"

namespace engine::scene::entities {
    /**
     * Representa a tag <scale> dos ficheiros XML.
     */
    class Scale: public Entity {
    private:
        glm::vec3 factors;

    public:
        Scale(const Scene& scene): Entity(scene) {}
        ~Scale() override = default;

        bool ParseXml(const tinyxml2::XMLNode *node) override;
        void Render() const override;
    };
}

#endif //CG_TP_ENGINE_SRC_ENTITIES_SCALE_H_
