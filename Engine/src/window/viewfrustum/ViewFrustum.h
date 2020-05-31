#ifndef CG_TP_ENGINE_SRC_WINDOW_CAMERAS_VIEWFRUSTUM_H_
#define CG_TP_ENGINE_SRC_WINDOW_CAMERAS_VIEWFRUSTUM_H_

#include "Plane.h"

namespace engine::window::viewfrustum {
    /**
     * Implementação de um View Frustum e de View Frustum Culling baseado no método de verificação
     * em Clip Space, tal como descrito em
     * http://www.lighthouse3d.com/tutorials/view-frustum-culling/clip-space-approach-extracting-the-planes/ .
     *
     * Este método foi o escolhido pois é capaz, por si próprio, de ajustar internamente as suas contas
     * conforme a posição dos objetos que estamos a tentar desenhar. Isto é extremamente útil pois a
     * pipeline de renderização, como está atualmente implementada, não permite que seja possível
     * perceber qual a posição de um Model quando este está a ser renderizado, nem o seu tamanho, e portanto,
     * torna possível uma implementação eficiente de View Frustum Culling sem ser necessário reorganizar todo
     * o processo de renderização de cenas.
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
         * @return False if the given sphere falls completely outside the view frustum, true otherwise
         */
        bool IsSphereInFrustum(const glm::vec3& center, const float& radius) const;

        /**
         * Tests if a sphere centered on (0, 0, 0) and with radius 1 would intersect with the view frustum.
         *
         * @return True if the sphere should render, false otherwise
         */
        static inline bool UnitSphereShouldRender() {
            return ViewFrustum().IsSphereInFrustum(glm::vec3(0.0f), 1.0f);
        }
    };
}

#endif //CG_TP_ENGINE_SRC_WINDOW_CAMERAS_VIEWFRUSTUM_H_
