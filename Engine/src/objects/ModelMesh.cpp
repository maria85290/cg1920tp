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

            AddVertex(x, y, z);
            AddNormal(nx, ny, nz);
            AddTexCoord(tx, ty);
        }

        file.close();

        this->numVertices = this->vertices.size();

        this->GenVBOs();
        this->vertices.clear();
        this->normals.clear();
        this->texCoords.clear();
        this->indices.clear();
    }

    void ModelMesh::GenVBOs()
    {
        glGenBuffers(sizeof(this->vbos) / sizeof(this->vbos[0]), this->vbos);

        // vbos[0] stores the vertex coordinates
        glBindBuffer(GL_ARRAY_BUFFER, this->vbos[0]);
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), this->vertices.data(), GL_STATIC_DRAW);

        // vbos[1] stores the normal coordinates
        glBindBuffer(GL_ARRAY_BUFFER, this->vbos[1]);
        glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(glm::vec3), this->normals.data(), GL_STATIC_DRAW);

        // vbos[2] stores the texture coordinates
        glBindBuffer(GL_ARRAY_BUFFER, this->vbos[2]);
        glBufferData(GL_ARRAY_BUFFER, this->texCoords.size() * sizeof(glm::vec2), this->texCoords.data(), GL_STATIC_DRAW);

        // vbos[3] stores the indices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbos[3]);
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
        glEnableClientState(GL_INDEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glBindBuffer(GL_ARRAY_BUFFER, this->vbos[0]);
        glVertexPointer(3, GL_FLOAT, 0, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, this->vbos[1]);
        glNormalPointer(GL_FLOAT, 0, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, this->vbos[2]);
        glTexCoordPointer(2, GL_FLOAT, 0, nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->vbos[3]);

        glDrawElements(GL_TRIANGLES, this->numIndices, GL_UNSIGNED_SHORT, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_INDEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
}
