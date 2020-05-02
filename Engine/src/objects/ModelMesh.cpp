#include "ModelMesh.h"

#include <fstream>
#include <string>

using std::ifstream;
using std::string;

namespace engine::objects {
    ObjectCache<ModelMesh> ModelMesh::cache;

    ModelMesh::ModelMesh(const string &filename): filename(filename) {
        ifstream file(filename);

        file >> this->numIndices;

        for(int i = 0; i < numIndices; i++) {
            int v;
            file >> v;

            this->indices.push_back(v);
        }

        float x, y, z;
        while(file >> x >> y >> z) {
            AddVertex(x, y, z);
        }

        file.close();

        this->numVertices = this->vertices.size();

        this->GenVBOs();
        this->vertices.clear();
        this->indices.clear();
    }

    void ModelMesh::GenVBOs()
    {
        glGenBuffers(2, this->vbos);

        glBindBuffer(GL_ARRAY_BUFFER, this->vbos[0]);
        glBufferData(GL_ARRAY_BUFFER, this->numVertices * sizeof(glm::vec3), this->vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbos[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->numIndices * sizeof(unsigned short), this->indices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    ModelMesh::~ModelMesh() {
        glDeleteBuffers(2, this->vbos);
    }

    void ModelMesh::Render() const {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_INDEX_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, this->vbos[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbos[1]);

        glVertexPointer(3, GL_FLOAT, 0, nullptr);
        glDrawElements(GL_TRIANGLES, this->numIndices, GL_UNSIGNED_SHORT, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_INDEX_ARRAY);
    }
}
