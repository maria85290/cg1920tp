#include "ModelMesh.h"

#include <fstream>
#include <string>

using std::ifstream;
using std::string;

namespace engine::objects {
    ObjectCache<ModelMesh> ModelMesh::cache;

    ModelMesh::ModelMesh(const string &filename): filename(filename) {
        ifstream file(filename);

        float x, y, z;
        while(file >> x >> y >> z) {
            AddVertex(x, y, z);
        }

        file.close();

        this->GenVBOs();
    }

    void ModelMesh::GenVBOs()
    {
        glEnableClientState(GL_VERTEX_ARRAY);

        glGenBuffers(1, &this->vbo);

        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, 3 * this->vertices.size() * sizeof(float), this->vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDisableClientState(GL_VERTEX_ARRAY);

        this->numVertices = this->vertices.size();
        this->vertices.clear();
    }

    ModelMesh::~ModelMesh() {
        glDeleteBuffers(1, &this->vbo);
    }

    void ModelMesh::Render() const {
        glEnableClientState(GL_VERTEX_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

        glVertexPointer(3, GL_FLOAT, 0, nullptr);
        glDrawArrays(GL_TRIANGLES, 0, this->numVertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDisableClientState(GL_VERTEX_ARRAY);
    }
}
