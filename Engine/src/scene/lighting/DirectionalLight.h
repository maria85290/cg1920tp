#ifndef CG_TP_ENGINE_SRC_SCENE_ENTITIES_LIGHTING_DIRECTIONALLIGHT_H_
#define CG_TP_ENGINE_SRC_SCENE_ENTITIES_LIGHTING_DIRECTIONALLIGHT_H_

#include "PointLight.h"

namespace engine::scene::lighting {
    /**
     * Representa o tipo de luz direcional, e a correspondente tag XML <light>.
     */
    class DirectionalLight: public PointLight {
    public:
        bool ParseXml(const tinyxml2::XMLNode *lightNode) override;
    };
}

#endif //CG_TP_ENGINE_SRC_SCENE_ENTITIES_LIGHTING_DIRECTIONALLIGHT_H_
