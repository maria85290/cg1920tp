#ifndef CG_TP_ENGINE_SRC_ENTITIES_MODELS_H_
#define CG_TP_ENGINE_SRC_ENTITIES_MODELS_H_

#include "Entity.h"
#include "Model.h"

namespace engine::scene::entities {
    /**
     * Representa a tag <models> dos ficheiros XML.
     */
    class Models: public Entity {
    private:
        std::vector<Model*> models;

        void AddModel(Model* model) {
            models.push_back(model);
        }

    public:
        Models(const Scene& scene): Entity(scene) {}
        ~Models();

        bool ParseXml(const tinyxml2::XMLNode *node) override;
        void Render() const override;
    };
}

#endif //CG_TP_ENGINE_SRC_ENTITIES_MODELS_H_
