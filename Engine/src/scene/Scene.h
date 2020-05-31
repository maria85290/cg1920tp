#ifndef CG_TP_ENGINE_SRC_SCENE_H_
#define CG_TP_ENGINE_SRC_SCENE_H_

#include <tinyxml2/tinyxml2.h>

#include "lighting/Lights.h"

namespace engine::scene::entities {
    class Group;
}

namespace engine::scene {
    /**
     * Representa uma cena renderizável no ecrã, e guarda a informação sobre todos os seus componentes.
     * Implementa também a funcionalidade de leitura de um ficheiro XML a partir do disco.
     */
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

        Scene(const Scene& scene) = delete;
        Scene& operator=(const Scene& other) = delete;

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

        /**
         * Liga as luzes, se estas tiverem sido definidas.
         */
        void EnableLights() const;

        /**
         * Desliga as luzes, se estas tiverem sido definidas.
         */
        void DisableLights() const;
    };
}

#endif //CG_TP_ENGINE_SRC_SCENE_H_
