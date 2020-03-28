#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <cstdio>
#include <cstdlib>

#include "../glut.h"

#include "Model.h"

using std::cout, std::endl, std::string, std::ifstream, std::vector, std::map;
using namespace std::chrono;

namespace engine::entities {
    map<string, const Model*> Model::loadedModels = map<string, const Model*>();

    Model::Model(const Model& model): filename(model.filename), vertices(vector<vec3>(model.vertices)), vbo(model.vbo), isVboOwned(false) {}

    Model::Model(const string& filename): filename(filename), isVboOwned(true) {
        ifstream file(filename);

        cout << "Loading model: " << filename << endl;
        auto startTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

        double x, y, z;
        while(file >> x >> y >> z) {
            AddVertex(x, y, z);
        }

        auto endTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

        auto elapsedTime = endTime - startTime;
        cout << "Model took " << elapsedTime << " milliseconds to load" << endl;

        Model::loadedModels[filename] = this;

        file.close();

        glGenBuffers(1, &this->vbo);

        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(double) * 3, this->vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Model::~Model() {
        if(this->isVboOwned) {
            glDeleteBuffers(1, &this->vbo);
        }
    }

/*    void Model::Render() const {
        glBegin(GL_TRIANGLES);

        for(const auto& v : vertices) {
            glVertex3d(v.x, v.y, v.z);
        }

        glEnd();
    }*/

    void Model::Render() const {
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glVertexPointer(3, GL_DOUBLE, 0, nullptr);
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
