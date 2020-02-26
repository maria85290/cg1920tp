#include <list>
#include <string>
#include <fstream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <iostream>
#endif

#include "Model.h"

Model::Model(const string& filename) {
    // TODO: Read model file
    ifstream file(filename);

    double x, y, z;
    while(file >> x >> y >> z) {
        AddVertex(x, y, z);
        cout << "[" << filename << "] " << x << " " << y << " " << z << endl;
    }

    file.close();

    cout << "Loaded model " << filename << endl;
}

void Model::Render() {
    glBegin(GL_TRIANGLES);

    for(auto& v : vertices_) {
        glVertex3d(v.x, v.y, v.z);
    }

    glEnd();

    cout << "Rendered model " << endl;
}
