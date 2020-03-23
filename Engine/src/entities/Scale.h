#ifndef CG_TP_ENGINE_SRC_ENTITIES_SCALE_H_
#define CG_TP_ENGINE_SRC_ENTITIES_SCALE_H_

#include <Common/vectors.h>

#include "Entity.h"

namespace entities {
    class Scale: public Entity {
    private:
        vec3 factors_;

    public:
        ~Scale() override = default;

        bool ParseXml(XMLNode *node) override;
        void Render() const override;
    };
}

#endif //CG_TP_ENGINE_SRC_ENTITIES_SCALE_H_
