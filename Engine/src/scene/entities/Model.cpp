#include "Model.h"
#include "../../objects/ObjectCache.h"

#include <string>
#include <fstream>
#include <iostream>
#include <memory>

using std::cout, std::cerr, std::endl, std::string, std::ifstream, std::vector, std::map;
using std::shared_ptr, std::make_shared;
using std::runtime_error;
using std::to_string;
using tinyxml2::XMLElement;

namespace engine::scene::entities {
    Model::Model(const tinyxml2::XMLElement* element)
    {
        const char* filename = element->Attribute("file");

        if(filename == nullptr) {
            throw runtime_error("Foi definido um modelo sem um ficheiro correspondente na linha " + to_string(element->GetLineNum()) + "!");
        }

        if(ModelMesh::GetCache().Contains(filename)) {
            this->mesh = ModelMesh::GetCache().Retrieve(filename);
        } else {
            this->mesh = ModelMesh::GetCache().Insert(filename, new ModelMesh(filename));
        }

        this->diffR = element->IntAttribute("diffR", 255);
        this->diffG = element->IntAttribute("diffG", 255);
        this->diffB = element->IntAttribute("diffB", 255);
    }

    void Model::Render() const {
        glPushAttrib(GL_COLOR_BUFFER_BIT);

        glColor3ub(diffR, diffG, diffB);
        this->mesh->Render();

        glPopAttrib();
    }
}
