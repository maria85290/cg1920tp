#include "Scene.h"

void Scene::Render() {
    for(auto& model : this->models_) {
        model.Render();
    }
}
