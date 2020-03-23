#include <string>
#include <fstream>

#include "../glut.h"

#include "Model.h"

namespace entities {
    Model::Model(const string& filename) {
        ifstream file(filename);

        double x, y, z;
        while(file >> x >> y >> z) {
            AddVertex(x, y, z);
        }

        file.close();
    }

    void Model::Render() const {
        glBegin(GL_TRIANGLES);

        for(const auto& v : vertices_) {
            glVertex3d(v.x, v.y, v.z);
        }

        glEnd();
    }
}
