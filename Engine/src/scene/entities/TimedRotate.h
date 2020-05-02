#ifndef CG_TP_ENGINE_SRC_SCENE_ENTITIES_TIMEDROTATE_H_
#define CG_TP_ENGINE_SRC_SCENE_ENTITIES_TIMEDROTATE_H_

#include <glm/vec3.hpp>

#include "Entity.h"

namespace engine::scene::entities {
    class TimedRotate: public Entity {
    private:
        /** The rotation time, in seconds. */
        int time;
        /** The rotation vector. */
        glm::vec3 vector;
        /** The current angle of the rotation. */
        double angle = 0;
        /** How much the angle goes forward every second. */
        double degreesPerSecond;

    public:
        ~TimedRotate() override = default;

        bool ParseXml(const tinyxml2::XMLNode *rotateNode) override;
        void Update(double deltaTime) override;
        void Render() const override;
    };
}

#endif //CG_TP_ENGINE_SRC_SCENE_ENTITIES_TIMEDROTATE_H_
