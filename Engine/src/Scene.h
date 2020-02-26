#ifndef CG_TP_ENGINE_SRC_SCENE_H_
#define CG_TP_ENGINE_SRC_SCENE_H_

#include <list>

#include "Model.h"

using namespace std;

class Scene {
private:
    list<Model> models_ = list<Model>();

public:
    void AddModel(const Model& model) {
        models_.push_front(model);
    }

    const list<Model>& GetModels() {
        return models_;
    }

    void Render();
};

#endif //CG_TP_ENGINE_SRC_SCENE_H_
