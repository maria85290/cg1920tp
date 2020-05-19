#ifndef CG_TP_ENGINE_SRC_SCENE_LIGHTING_SPOTLIGHT_H_
#define CG_TP_ENGINE_SRC_SCENE_LIGHTING_SPOTLIGHT_H_

#include <glm/glm.hpp>

#include "PointLight.h"

namespace engine::scene::lighting {
    class SpotLight: public PointLight {
    protected:
        glm::vec3 direction;

        float cutoffExponent;
        float cutoffAngle;

        float attenuationConstant;
        float attenuationLinear;
        float attenuationQuadratic;

    public:
        bool ParseXml(const tinyxml2::XMLNode *lightNode) override;
        void Enable() const override;
    };
}

#endif //CG_TP_ENGINE_SRC_SCENE_LIGHTING_SPOTLIGHT_H_
