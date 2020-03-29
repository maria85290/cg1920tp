#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <tinyxml2/tinyxml2.h>

#include "../glut.h"

#include "Model.h"

using std::cout, std::cerr, std::endl, std::string, std::ifstream, std::vector, std::map;
using tinyxml2::XMLElement;

namespace engine::entities {
    map<string, const Model*> Model::loadedModels = map<string, const Model*>();

    Model::Model(const Model& model, const double diffR, const double diffG, const double diffB): filename(model.filename), vertices(model.vertices),
	diffR(diffR), diffG(diffG), diffB(diffB),
	vbo(model.vbo),
	isCachedModel(false)
    {}

    Model::Model(const string& filename, const double diffR, const double diffG, const double diffB): filename(filename),
                                                                                    diffR(diffR), diffG(diffG), diffB(diffB),
                                                                                    isCachedModel(true) {
        this->vertices = new vector<vec3>;
    	
        ifstream file(filename);

        double x, y, z;
        while(file >> x >> y >> z) {
            AddVertex(x, y, z);
        }

        file.close();

        Model::loadedModels[filename] = this;

        this->GenVBOs();
    }

    Model::~Model() {
        if(this->isCachedModel) {
            delete this->vertices;
            this->vertices = nullptr;
        	
			Model::loadedModels.erase(filename);

            glDeleteBuffers(1, &this->vbo);
        }
    }

	void Model::GenVBOs()
	{
        glGenBuffers(1, &this->vbo);

        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, 3 * this->vertices->size() * sizeof(double), this->vertices->data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

    void Model::Render() const {
    	glEnableClientState(GL_VERTEX_ARRAY);
        glPushAttrib(GL_COLOR_BUFFER_BIT);
    	
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

        glColor3ub(diffR, diffG, diffB);
        glVertexPointer(3, GL_DOUBLE, 0, nullptr);
        glDrawArrays(GL_TRIANGLES, 0, this->vertices->size());

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glPopAttrib();
        glDisableClientState(GL_VERTEX_ARRAY);
    }

    const Model* Model::LoadModel(const XMLElement* element) {
        const char *filename = element->Attribute("file");

        if(filename == nullptr) {
            cerr << "Não existe campo 'file'." << endl;
            return nullptr;
        }

        double diffR = element->DoubleAttribute("diffR", 255.0);
        double diffG = element->DoubleAttribute("diffG", 255.0);
        double diffB = element->DoubleAttribute("diffB", 255.0);

        if(Model::loadedModels.count(filename) > 0) {
            const Model* model = Model::loadedModels.find(filename)->second;
            return new Model(*model, diffR, diffG, diffB);
        } else {
            return new Model(filename, diffR, diffG, diffB);
        }
    }
}
