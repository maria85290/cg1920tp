#ifndef CG_TP_ENGINE_SRC_ENTITIES_TRANSLATE_H_
#define CG_TP_ENGINE_SRC_ENTITIES_TRANSLATE_H_

#include <Common/vectors.h>
#include "Entity.h"

namespace entities {
    class Translate: public Entity {
    private:
        vec3 vector_;
    public:
        ~Translate() override = default;

        bool ParseXml(XMLNode *translateNode) override;
        void Render() const override;
    };
}

#endif //CG_TP_ENGINE_SRC_ENTITIES_TRANSLATE_H_
