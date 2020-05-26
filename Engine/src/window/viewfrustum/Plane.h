#ifndef CG_TP_ENGINE_SRC_WINDOW_VIEWFRUSTUM_PLANE_H_
#define CG_TP_ENGINE_SRC_WINDOW_VIEWFRUSTUM_PLANE_H_

#include <glm/glm.hpp>

namespace engine::window::viewfrustum {
    enum PlaneType { TOP = 0, BOTTOM, LEFT, RIGHT, NEAR, FAR };

    class Plane {
    private:
        glm::vec4 coeffs = {0, 0, 0, 0};

    public:
        Plane() = default;

        inline explicit Plane(const glm::vec4& coeffs) {
            // Definir os primeiros 3 componentes de coeffs como sendo o vector normal o plano,
            // e definir o último valor de coeffs como sendo o valor D da equação do plano
            this->coeffs = glm::vec4(glm::normalize(glm::vec3(coeffs)), coeffs.w);
        }

        inline float GetD() const {
            return this->coeffs.w;
        }

        inline glm::vec3 GetNormal() const {
            return {this->coeffs.x, this->coeffs.y, this->coeffs.z};
        }
    };
}

namespace glm {
    // Teach glm how to compute the distance from a plane to a point
    inline float distance(const engine::window::viewfrustum::Plane& plane, const glm::vec3& point) {
        return plane.GetD() + glm::dot(plane.GetNormal(), point);
    }
}

#endif //CG_TP_ENGINE_SRC_WINDOW_VIEWFRUSTUM_PLANE_H_
