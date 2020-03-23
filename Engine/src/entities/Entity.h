#ifndef CG_TP_ENGINE_SRC_ENTITIES_ENTITY_H_
#define CG_TP_ENGINE_SRC_ENTITIES_ENTITY_H_

#include <tinyxml2/tinyxml2.h>

using namespace tinyxml2;

namespace entities {
    class Entity {
    public:
        Entity() = default;
        virtual ~Entity() = default;

        virtual bool ParseXml(XMLNode *node) = 0;
        virtual void Render() const = 0;
    };
}

#endif //CG_TP_ENGINE_SRC_ENTITIES_ENTITY_H_
