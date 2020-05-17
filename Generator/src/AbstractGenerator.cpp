#include "AbstractGenerator.h"

#include <iostream>
#include <fstream>

using namespace std;

void AbstractGenerator::AddVertex(const glm::dvec3& v, const glm::dvec3& n, const glm::dvec2& t) {
    glm::dvec3 normal = n;

    if(glm::length(normal) > 0.2) {
        normal = glm::normalize(normal);
    }

    vertex_data vd = {v, normal, t};

    if(this->vertices.count(vd) == 0) {
        this->vertices[vd] = this->nextIndex++;
    }

    if(this->nextIndex == USHRT_MAX) {
        throw std::runtime_error("The requested model is too large! Please lower the model's generation parameters.");
    }

    int index = this->vertices[vd];

    this->indices.push_back(index);
}

void AbstractGenerator::SaveVerticesToFile() {
    ofstream file(filename);

    // Print the number of indices that will exist on the file
    file << this->indices.size() << endl;

    // Print each index to the file
    for(auto index : this->indices) {
        file << index << endl;
    }

    // Print each vertex to the file
    map<unsigned short, vertex_data> orderedVertices;

    for(auto pair : this->vertices) {
        orderedVertices[pair.second] = pair.first;
    }

    for(auto pair : orderedVertices) {
        auto vertexData = pair.second;

        auto vertex = vertexData.pos;
        auto normal = vertexData.normal;
        auto texCrd = vertexData.textureCoords;

        file << vertex.x << " " << vertex.y << " " << vertex.z << " "
             << normal.x << " " << normal.y << " " << normal.z << " "
             << texCrd.x << " " << texCrd.y << endl;
    }

    file.close();
}

bool vertex_data::operator==(const vertex_data& o) const {
    return o.pos == this->pos && o.normal == this->normal && o.textureCoords == this->textureCoords;
}

size_t std::hash<struct vertex_data>::operator()(const vertex_data& o) const {
    size_t res = 17;
    res = res * 31 + hash<glm::vec3>()( o.pos );
    res = res * 31 + hash<glm::vec3>()( o.normal );
    res = res * 31 + hash<glm::vec2>()( o.textureCoords );

    return res;
}
