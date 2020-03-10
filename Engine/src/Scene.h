#ifndef CG_TP_ENGINE_SRC_SCENE_H_
#define CG_TP_ENGINE_SRC_SCENE_H_

#include <vector>

#include "Model.h"

using namespace std;

class Scene {
private:
    vector<Model> models_ = vector<Model>();

public:
    void AddModel(const Model& model) {
        models_.push_back(model);
    }

    const vector<Model>& GetModels() {
        return models_;
    }

    void Render();
};

#endif //CG_TP_ENGINE_SRC_SCENE_H_
