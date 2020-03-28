#ifndef CG_TP_ENGINE_SRC_ENTITIES_SCALE_H_
#define CG_TP_ENGINE_SRC_ENTITIES_SCALE_H_

#include <Common/vectors.h>

#include "Entity.h"

namespace engine::entities {
    class Scale: public Entity {
    private:
        vec3 factors;

    public:
        ~Scale() override = default;

        bool ParseXml(tinyxml2::XMLNode *node) override;
        void Render() const override;
    };
}

#endif //CG_TP_ENGINE_SRC_ENTITIES_SCALE_H_
