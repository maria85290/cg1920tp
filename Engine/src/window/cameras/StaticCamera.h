#ifndef CG_TP_ENGINE_SRC_WINDOW_CAMERAS_STATICCAMERA_H_
#define CG_TP_ENGINE_SRC_WINDOW_CAMERAS_STATICCAMERA_H_

#include "Camera.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace engine::window::cameras {
    /**
     * Implementação de uma câmara estática, que não pode ser mexida, nem se movimenta no mundo.
     */
    class StaticCamera: public Camera {
    private:
        glm::dvec3 position;
        glm::dvec3 lookingAt;
    public:
        explicit StaticCamera(glm::dvec3 position, glm::dvec3 lookingAt);

        void PrintInfo() const override {}
    };
}

#endif //CG_TP_ENGINE_SRC_WINDOW_CAMERAS_STATICCAMERA_H_
