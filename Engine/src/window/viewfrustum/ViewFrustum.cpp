#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <iostream>

#include "ViewFrustum.h"
#include "Plane.h"

namespace engine::window::viewfrustum {
    ViewFrustum::ViewFrustum() {
        glm::mat4 projectionMatrix, modelViewMatrix;

        glGetFloatv(GL_PROJECTION_MATRIX, glm::value_ptr(projectionMatrix));
        glGetFloatv(GL_MODELVIEW_MATRIX, glm::value_ptr(modelViewMatrix));

        glm::mat4 A = projectionMatrix * modelViewMatrix;

        planes[PlaneType::NEAR]   = Plane( A[2] + A[3]);
        planes[PlaneType::FAR]    = Plane(-A[2] + A[3]);

        planes[PlaneType::TOP]    = Plane(-A[1] + A[3]);
        planes[PlaneType::BOTTOM] = Plane( A[1] + A[3]);

        planes[PlaneType::LEFT]   = Plane( A[0] + A[3]);
        planes[PlaneType::RIGHT]  = Plane(-A[0] + A[3]);
    }

    bool ViewFrustum::IsSphereInFrustum(const glm::vec3& center, const float& radius) const {
        int out = 0;

        for(int i = 0; i < 6; i++) {
            float distance = glm::distance(planes[i % 6], center) - radius;

            if(distance < -1.0f)
                out++;
        }

        return out < 6;
    }
}
