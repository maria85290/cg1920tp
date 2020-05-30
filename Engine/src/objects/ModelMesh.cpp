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
        float nx, ny, nz;
        float tx, ty;
        while(file >>  x >>  y >>  z
                   >> nx >> ny >> nz
                   >> tx >> ty) {

            AddVertex(x, y, z,
                      nx, ny, nz,
                      tx, ty);
        }

        file.close();

        this->GenVBOs();
        this->vertexData.clear();
        this->indices.clear();
    }

    void ModelMesh::GenVBOs()
    {
        glGenBuffers(sizeof(this->vbos) / sizeof(this->vbos[0]), this->vbos);

        // vbos[0] stores the following:
        // First 3 bytes are vertex coordinates
        // Next 3 bytes are normal coordinates
        // Next 2 bytes are texture coordinates
        glBindBuffer(GL_ARRAY_BUFFER, this->vbos[0]);
        glBufferData(GL_ARRAY_BUFFER, this->vertexData.size() * sizeof(struct vertex_data), this->vertexData.data(), GL_STATIC_DRAW);

        // vbos[1] stores the indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbos[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->numIndices * sizeof(unsigned short), this->indices.data(), GL_STATIC_DRAW);

        // Unbind the buffers
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    ModelMesh::~ModelMesh() {
        glDeleteBuffers(sizeof(this->vbos) / sizeof(this->vbos[0]), this->vbos);
    }

    void ModelMesh::Render() const {
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_INDEX_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, this->vbos[0]);

        glVertexPointer(3,   GL_FLOAT,  2 * sizeof(glm::vec3) + sizeof(glm::vec2), 0);
        glNormalPointer(     GL_FLOAT,  sizeof(glm::vec2) + 2 * sizeof(glm::vec3), reinterpret_cast<const void*>(sizeof(glm::vec3)));
        glTexCoordPointer(2, GL_FLOAT,  2 * sizeof(glm::vec3) + sizeof(glm::vec2), reinterpret_cast<const void*>(sizeof(glm::vec3) + sizeof(glm::vec3)));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbos[1]);
        glDrawElements(GL_TRIANGLES, this->numIndices, GL_UNSIGNED_SHORT, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_INDEX_ARRAY);
    }
}
