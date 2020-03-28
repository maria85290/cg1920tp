#ifndef CG_TP_ENGINE_SRC_ENTITIES_ENTITY_H_
#define CG_TP_ENGINE_SRC_ENTITIES_ENTITY_H_

#include <tinyxml2/tinyxml2.h>
#include <iostream>

#include "../glut.h"

namespace engine::entities {
    class Entity {
    public:
        Entity() = default;
        virtual ~Entity() = default;

        virtual bool ParseXml(tinyxml2::XMLNode *node) = 0;
        virtual void Render() const = 0;
    };
}

#endif //CG_TP_ENGINE_SRC_ENTITIES_ENTITY_H_
