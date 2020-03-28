#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

#include "../glut.h"

#include "Model.h"

using std::cout, std::endl, std::string, std::ifstream;
using namespace std::chrono;

namespace engine::entities {
    Model::Model(const string& filename) {
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

        file.close();
    }

    void Model::Render() const {
        glBegin(GL_TRIANGLES);

        for(const auto& v : vertices) {
            glVertex3d(v.x, v.y, v.z);
        }

        glEnd();
    }
}
