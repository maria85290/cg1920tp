#ifndef CG_TP_ENGINE_SRC_SCENE_H_
#define CG_TP_ENGINE_SRC_SCENE_H_

#include <tinyxml2/tinyxml2.h>

#include "entities/Group.h"

namespace engine {
    class Scene {
    private:
        std::vector<const entities::Group*> groups = std::vector<const entities::Group*>();

        void AddGroup(const entities::Group* group) {
            groups.push_back(group);
        }

    public:
        ~Scene();

        /**
         * Lê do ficheiro XML a tag corresponde à cena que vai ser renderizada.
         *
         * @param sceneNode O nodo corresponde à cena
         * @return true se correu tudo bem, false caso contrário
         */
        bool ParseXml(tinyxml2::XMLNode* sceneNode);

        /**
         * Inicializa definições do OpenGL que vão ser necessárias para todas as entidades da cena.
         */
        void InitGLSettings() const;

        /**
         * Limpa o ecrã de todas as imagens desenhadas na última frame.
         */
        void ClearPreviousFrame() const;
        /**
         * Desenha uma nova frame desta cena.
         */
        void Render() const;
    };
}

#endif //CG_TP_ENGINE_SRC_SCENE_H_
