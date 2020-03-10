#include <string>
#include <fstream>

#include "glut.h"

#include "Model.h"

Model::Model(const string& filename) {
    ifstream file(filename);

    double x, y, z;
    while(file >> x >> y >> z) {
        AddVertex(x, y, z);
    }

    file.close();
}

void Model::Render() {
    glBegin(GL_TRIANGLES);

    for(auto& v : vertices_) {
        glVertex3d(v.x, v.y, v.z);
    }

    glEnd();
}
