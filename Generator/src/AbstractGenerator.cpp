#include "AbstractGenerator.h"

using std::endl;

void AbstractGenerator::AddVertex(const glm::vec3& v) {
    if(this->vertices.count(v) == 0) {
        this->vertices[v] = this->nextIndex++;
    }

    this->indices.push_back(this->vertices[v]);
}

void AbstractGenerator::SaveVerticesToFile() {
    std::ofstream file(filename);

    // Print the number of indices that will exist on the file
    file << this->indices.size() << endl;

    // Print each index to the file
    for(auto index : this->indices) {
        file << index << endl;
    }

    // Print each vertex to the file
    std::map<unsigned short, glm::vec3> orderedVertices;

    for(auto pair : this->vertices) {
        orderedVertices[pair.second] = pair.first;
    }

    for(auto pair : orderedVertices) {
        auto vertex = pair.second;

        file << vertex.x << " "
             << vertex.y << " "
             << vertex.z << endl;
    }

    file.close();
}
