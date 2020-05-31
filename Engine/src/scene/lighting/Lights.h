#ifndef CG_TP_ENGINE_SRC_SCENE_ENTITIES_LIGHTS_H_
#define CG_TP_ENGINE_SRC_SCENE_ENTITIES_LIGHTS_H_

#include <vector>

#include "Light.h"

namespace engine::scene::lighting {
    /**
     * Representa a tag <lights> presente no topo de um ficheiro XMl de uma cena.
     */
    class Lights {
    private:
        std::vector<Light*> lights;
    public:
        ~Lights();

        bool ParseXml(const tinyxml2::XMLNode *groupNode);
        void Enable() const;
        void Disable() const;
    };
}

#endif //CG_TP_ENGINE_SRC_SCENE_ENTITIES_LIGHTS_H_
