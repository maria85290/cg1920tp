#ifndef CG_TP_ENGINE_SRC_ENTITIES_ROTATE_H_
#define CG_TP_ENGINE_SRC_ENTITIES_ROTATE_H_

#include <Common/vectors.h>
#include "Entity.h"

namespace engine::entities {
    class Rotate: public Entity {
    private:
        /** The rotation angle, in degrees. */
        double angle;
        /** The rotation vector. */
        vec3 vector;

    public:
        ~Rotate() override = default;

        bool ParseXml(tinyxml2::XMLNode *rotateNode) override;
        void Render() const override;
    };
}

#endif //CG_TP_ENGINE_SRC_ENTITIES_ROTATE_H_
