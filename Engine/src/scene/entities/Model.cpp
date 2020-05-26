#include "Model.h"

#include <string>
#include <fstream>
#include <iostream>
#include <memory>

#include <glm/gtc/type_ptr.hpp>

#include "../../objects/ObjectCache.h"
#include "../../objects/Texture.h"
#include "../lighting/Light.h"
#include "../../window/viewfrustum/ViewFrustum.h"

using std::cout, std::cerr, std::endl, std::string, std::ifstream, std::vector, std::map;
using std::shared_ptr, std::make_shared;
using std::runtime_error;
using std::to_string;
using tinyxml2::XMLElement;

using engine::objects::Texture;
using engine::scene::lighting::Light;
using engine::window::viewfrustum::ViewFrustum;

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

        this->ambientLight = Light::ParseLightComponent("amb", element, {0.2f, 0.2f, 0.2f, 1.0f});
        this->diffuseLight = Light::ParseLightComponent("diff", element, {0.8f, 0.8f, 0.8f, 1.0f});
        this->specularLight = Light::ParseLightComponent("spec", element, {0.0f, 0.0f, 0.0f, 1.0f});
        this->emissionLight = Light::ParseLightComponent("emiss", element, {0.0f, 0.0f, 0.0f, 1.0f});
        this->shininess = element->FloatAttribute("shininess", 0);
    }

    void Model::Render() const {
        // TODO: Change the generator to automatically provide the radius in the model's file
        // At this point in the rendering stage, the current OpenGL Matrix says that we are currently in local space
        // i.e., the current object is always centered at (0,0,0).
        // The model file will already have provided the radius for the bounding sphere, so we just plug that in
        // here as well
        // Note: If GL_CULL_FACE isn't enabled, we don't view frustum cull, because otherwise the F1 debug feature
        // becomes useless
        if(!ViewFrustum::SphereInFrustum(glm::vec3(0), 1.0f) && glIsEnabled(GL_CULL_FACE))
            return;

        glPushAttrib(GL_COLOR_BUFFER_BIT);
        glPushAttrib(GL_LIGHTING_BIT);

        glColor3fv(glm::value_ptr(this->diffuseLight));

        glMaterialfv(GL_FRONT, GL_AMBIENT, glm::value_ptr(this->ambientLight));
        glMaterialfv(GL_FRONT, GL_DIFFUSE, glm::value_ptr(this->diffuseLight));
        glMaterialfv(GL_FRONT, GL_SPECULAR, glm::value_ptr(this->specularLight));
        glMaterialfv(GL_FRONT, GL_EMISSION, glm::value_ptr(this->emissionLight));
        glMaterialf(GL_FRONT, GL_SHININESS, this->shininess);

        if(this->texture)
            this->texture->Bind();

        this->mesh->Render();

        if(this->texture)
            this->texture->Unbind();

        glPopAttrib();
        glPopAttrib();
    }
}
