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

        /**
         * Função responsável pela leitura da secção do ficheiro XML corresponde a esta entidade.
         * @param node O nodo do ficheiro XML correspondente a esta entidade.
         * @return true se o parsing se deu corretamente; false caso contrário
         */
        virtual bool ParseXml(tinyxml2::XMLNode *node) = 0;
        /**
         * Função responsável por renderizar esta entidade no ecrã.
         */
        virtual void Render() const = 0;
    };
}

#endif //CG_TP_ENGINE_SRC_ENTITIES_ENTITY_H_
