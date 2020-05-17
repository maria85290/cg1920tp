#ifndef CG_TP_ENGINE_SRC_SCENE_H_
#define CG_TP_ENGINE_SRC_SCENE_H_

#include <tinyxml2/tinyxml2.h>

#include "entities/Group.h"
#include "lighting/Lights.h"

namespace engine::scene {
    class Scene {
    private:
        lighting::Lights* lights = nullptr;
        std::vector<entities::Group*> groups;

        void AddGroup(entities::Group* group) {
            groups.push_back(group);
        }

    public:
        Scene() = default;
        ~Scene();

        /**
         * Lê do ficheiro XML a tag corresponde à cena que vai ser renderizada.
         *
         * @param sceneNode O nodo corresponde à cena
         * @return true se correu tudo bem, false caso contrário
         */
        bool ParseXml(const tinyxml2::XMLNode* sceneNode);

        /**
         * Inicializa definições do OpenGL que vão ser necessárias para todas as entidades da cena.
         */
        void InitGLSettings() const;

        /**
         * Limpa o ecrã de todas as imagens desenhadas na última frame.
         */
        void ClearPreviousFrame() const;

        /**
         * Função responsável por atualizar os parãmetros internos de cada identidade, se necessário.
         * @param deltaTime
         */
        void Update(double deltaTime);

        /**
         * Desenha uma nova frame desta cena.
         */
        void Render() const;
    };
}

#endif //CG_TP_ENGINE_SRC_SCENE_H_
