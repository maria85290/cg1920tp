#include <list>

#include "tinyxml2/tinyxml2.h"
#include "Model.cpp"

class Scene {
    private:
        std::list<Model> models_ = std::list<Model>();

    public:
        void addModel(const Model& model) {
            models_.push_front(model);
        }

        list<Model> getModels_() {
            return models_;
        }
};