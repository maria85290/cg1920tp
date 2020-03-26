#ifndef CG_TP_ENGINE_SRC_ENTITIES_MODELS_H_
#define CG_TP_ENGINE_SRC_ENTITIES_MODELS_H_

#include "Entity.h"
#include "Model.h"

namespace engine::entities {
    class Models: public Entity {
    private:
        vector<const Model*> models = vector<const Model*>();

        void AddModel(const Model* model) {
            models.push_back(model);
        }

    public:
        bool ParseXml(XMLNode *node) override;
        void Render() const override;
    };
}

#endif //CG_TP_ENGINE_SRC_ENTITIES_MODELS_H_
