#ifndef CG_TP_ENGINE_SRC_ENTITIES_TRANSLATE_H_
#define CG_TP_ENGINE_SRC_ENTITIES_TRANSLATE_H_

#include <glm/vec3.hpp>
#include "Entity.h"

namespace engine::scene::entities {
    /**
     * Representa a tag <translate> dos ficheiros XML, na sua versão estática, i.e.,
     * na versão em que não existem nódos-filho desta tag. Isso significa que a
     * translação deve acontecer sempre para a mesma posição todas as frames.
     */
    class StaticTranslate: public Entity {
    private:
        glm::vec3 vector;
    public:
        StaticTranslate(const Scene& scene): Entity(scene) {}
        ~StaticTranslate() override = default;

        bool ParseXml(const tinyxml2::XMLNode *translateNode) override;
        void Render() const override;
    };
}

#endif //CG_TP_ENGINE_SRC_ENTITIES_TRANSLATE_H_
