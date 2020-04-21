#ifndef CG_TP_ENGINE_SRC_ENTITIES_TRANSLATE_H_
#define CG_TP_ENGINE_SRC_ENTITIES_TRANSLATE_H_

#include <glm/vec3.hpp>
#include "Entity.h"

namespace engine::scene::entities {
    class Translate: public Entity {
    private:
        glm::vec3 vector;
    public:
        ~Translate() override = default;

        bool ParseXml(const tinyxml2::XMLNode *translateNode) override;
        void Render() const override;
    };
}

#endif //CG_TP_ENGINE_SRC_ENTITIES_TRANSLATE_H_
