#ifndef CG_TP_ENGINE_SRC_WINDOW_CAMERAS_VIEWFRUSTUM_H_
#define CG_TP_ENGINE_SRC_WINDOW_CAMERAS_VIEWFRUSTUM_H_

#include "Plane.h"

namespace engine::window::viewfrustum {
    /**
     * Implementação de um View Frustum e de View Frustum Culling baseado no método de verificação
     * em Clip Space, tal como descrito em
     * http://www.lighthouse3d.com/tutorials/view-frustum-culling/clip-space-approach-extracting-the-planes/ .
     */
    class ViewFrustum {
    private:
        Plane planes[6];

    public:
        ViewFrustum();

        /**
         * Tests if the given sphere intersects the view frustum.
         *
         * @param center The center of the sphere
         * @param radius The radius of the sphere
         *
         * @return True if the given sphere falls completely inside the view frustum, false otherwise
         */
        bool IsSphereInFrustum(const glm::vec3& center, const float& radius) const;

        static inline bool SphereInFrustum(const glm::vec3& center, const float& radius) {
            return ViewFrustum().IsSphereInFrustum(center, radius);
        }
    };
}

#endif //CG_TP_ENGINE_SRC_WINDOW_CAMERAS_VIEWFRUSTUM_H_
