#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

#include "../glut.h"

#include "Model.h"

using std::cout, std::endl, std::string, std::ifstream, std::vector, std::map;
using namespace std::chrono;

namespace engine::entities {
    map<string, const Model*> Model::loadedModels = map<string, const Model*>();

    Model::Model(const Model& model): filename(model.filename), vertices(vector<vec3>(model.vertices)), vbo(model.vbo), isVboOwned(false) {}

    Model::Model(const string& filename): filename(filename), isVboOwned(true) {
        ifstream file(filename);

        double x, y, z;
        while(file >> x >> y >> z) {
            AddVertex(x, y, z);
        }

        file.close();

        Model::loadedModels[filename] = this;

        glGenBuffers(1, &this->vbo);

        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, 3 * this->vertices.size() * sizeof(double), this->vertices.data(), GL_STATIC_DRAW);
        glVertexPointer(3, GL_DOUBLE, 0, nullptr);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Model::~Model() {
        if(this->isVboOwned) {
            glDeleteBuffers(1, &this->vbo);

            Model::loadedModels.erase(filename);
        }
    }

    void Model::Render() const {
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    const Model* Model::LoadModel(const string &filename) {
        if(Model::loadedModels.count(filename) > 0) {
            const Model* model = Model::loadedModels.find(filename)->second;
            return new Model(*model);
        } else {
            return new Model(filename);
        }
    }
}
