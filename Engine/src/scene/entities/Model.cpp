#include "Model.h"
#include "../../objects/ObjectCache.h"
#include "../../objects/Texture.h"

#include <string>
#include <fstream>
#include <iostream>
#include <memory>

using std::cout, std::cerr, std::endl, std::string, std::ifstream, std::vector, std::map;
using std::shared_ptr, std::make_shared;
using std::runtime_error;
using std::to_string;
using tinyxml2::XMLElement;

using engine::objects::Texture;

namespace engine::scene::entities {
    Model::Model(const tinyxml2::XMLElement* element)
    {
        const char* meshFilename = element->Attribute("file");

        if(meshFilename == nullptr) {
            throw runtime_error("Foi definido um modelo sem um ficheiro correspondente na linha " + to_string(element->GetLineNum()) + "!");
        }

        if(ModelMesh::GetCache().Contains(meshFilename)) {
            this->mesh = ModelMesh::GetCache().Retrieve(meshFilename);
        } else {
            this->mesh = ModelMesh::GetCache().Insert(meshFilename, new ModelMesh(meshFilename));
        }

        const char* textureFilename = element->Attribute("texture");

        // Textures are optional.
        if(textureFilename != nullptr) {
            if(Texture::GetCache().Contains(textureFilename)) {
                this->texture = Texture::GetCache().Retrieve(textureFilename);
            } else {
                this->texture = Texture::GetCache().Insert(textureFilename, new Texture(textureFilename));
            }
        }

        this->diffR = element->IntAttribute("diffR", 255);
        this->diffG = element->IntAttribute("diffG", 255);
        this->diffB = element->IntAttribute("diffB", 255);
    }

    void Model::Render() const {
        glPushAttrib(GL_COLOR_BUFFER_BIT);

        glColor3ub(diffR, diffG, diffB);

        if(this->texture)
            this->texture->Bind();

        this->mesh->Render();

        if(this->texture)
            this->texture->Unbind();

        glPopAttrib();
    }
}
