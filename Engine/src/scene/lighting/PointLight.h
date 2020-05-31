#ifndef CG_TP_ENGINE_SRC_SCENE_ENTITIES_LIGHTING_POINTLIGHT_H_
#define CG_TP_ENGINE_SRC_SCENE_ENTITIES_LIGHTING_POINTLIGHT_H_

#include <string>

#include "Light.h"

namespace engine::scene::lighting {
    /**
     * Representa o tipo de luz de ponto, e a correspondente tag XML <light>.
     */
    class PointLight: public Light {
    protected:
        glm::vec4 position;

    public:
        bool ParseXml(const tinyxml2::XMLNode *lightNode) override;
        void Enable() const override;
    };
}

#endif //CG_TP_ENGINE_SRC_SCENE_ENTITIES_LIGHTING_POINTLIGHT_H_
