#include "CatmullRomAnimation.h"
#include "../../util/Settings.h"

#include <string>
#include <tuple>
#include <glm/gtc/type_ptr.hpp>

using tinyxml2::XML_SUCCESS;

using std::string, std::pair, std::vector;
using std::cerr, std::endl;
using tinyxml2::XMLComment;

namespace engine::scene::entities {

    /** A matriz de coeficientes para animações com Catmull-Rom Splines. Em formato column-major. */
    glm::mat4 CatmullRomAnimation::coefficientMatrix = {
        { -0.5f,  1.0f, -0.5f,  0.0f },
        {  1.5f, -2.5f,  0.0f,  1.0f },
        { -1.5f,  2.0f,  0.5f,  0.0f },
        {  0.5f, -0.5f,  0.0f,  0.0f }
    };

    bool CatmullRomAnimation::ParseXml(const tinyxml2::XMLNode *translateNode) {
        // First, parse the time from the node
        auto elem = translateNode->ToElement();

        int time;
        if(elem->QueryAttribute("time", &time) != XML_SUCCESS) {
            cerr << "Failed to parse the animation time from the translate node!" << endl;
            return false;
        }

        // Second, parse all of the control points
        auto currNode = translateNode->FirstChild();

        while(currNode != nullptr) {
            if(dynamic_cast<const XMLComment*>(currNode)) {
                currNode = currNode->NextSibling();
                continue;
            }

            string nodeName(currNode->Value());

            if(nodeName != "point") {
                cerr << "Found non-point node inside of translate node!" << endl;
                return false;
            }

            auto currElem = currNode->ToElement();

            glm::vec4 v(1.0f);

            if(currElem->QueryAttribute("X", &v.x) != XML_SUCCESS) {
                cerr << "Failed to parse element X from point node!" << endl;
                return false;
            }

            if(currElem->QueryAttribute("Y", &v.y) != XML_SUCCESS) {
                cerr << "Failed to parse element Y from point node!" << endl;
                return false;
            }

            if(currElem->QueryAttribute("Z", &v.z) != XML_SUCCESS) {
                cerr << "Failed to parse element Z from point node!" << endl;
                return false;
            }

            this->controlPoints.push_back(v);

            currNode = currNode->NextSibling();
        }

        // Let's figure out the rate at which t must change for the animation to happen every "time" seconds
        this->tPerSecond = 1.0f / time;

        // Let's generate the full curve rendering ahead of time
        this->GenerateCurveRendering();

        return true;
    }

    void CatmullRomAnimation::Update(double deltaTime) {
        this->t += this->tPerSecond * float(deltaTime);

        auto [position, deriv] = this->GetGlobalCatmullRomPoint(this->t);

        this->position = position;

        glm::vec3 x = glm::normalize(deriv);
        glm::vec3 z = glm::normalize(glm::cross(x, y));
                  y = glm::normalize(glm::cross(z, x));

        this->orientation = glm::mat4(
            glm::vec4(x, 0.0f),
            glm::vec4(y, 0.0f),
            glm::vec4(z, 0.0f),
            glm::vec4(glm::vec3(0.0f), 1.0f)
        );
    }

    void CatmullRomAnimation::Render() const {
        // Render the curve itself
        if(Settings::Contains("debug")) {
            this->GetScene().DisableLights();

            glEnableClientState(GL_VERTEX_ARRAY);

            glBindBuffer(GL_ARRAY_BUFFER, this->curveVbo);
            glVertexPointer(3, GL_FLOAT, 0, nullptr);

            glDrawArrays(GL_LINE_LOOP, 0, this->numCurveVertices);

            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glDisableClientState(GL_VERTEX_ARRAY);

            this->GetScene().EnableLights();
        }

        // Now position the next entities in the pipeline properly,
        // by applying the proper transformations to the OpenGL State
        glTranslatef(this->position.x, this->position.y, this->position.z);
        glMultMatrixf(glm::value_ptr(this->orientation));
    }

    const pair<glm::vec3, glm::vec3> CatmullRomAnimation::GetCatmullRomPoint(float t,
        const glm::vec4& p0, const glm::vec4& p1, const glm::vec4& p2, const glm::vec4& p3) {

        glm::mat4 A = this->coefficientMatrix * glm::transpose(glm::mat4(p0, p1, p2, p3));

        glm::vec4 pos(powf(t, 3), powf(t, 2), t, 1.0f);
        glm::vec4 deriv(3.0f * powf(t, 2), 2.0f * t, 1.0f, 0.0f);

        return {pos * A, deriv * A};
    }

    const pair<glm::vec3, glm::vec3> CatmullRomAnimation::GetGlobalCatmullRomPoint(float gt) {
        const int numPoints = static_cast<int>(this->controlPoints.size());

        float t = gt * numPoints;
        int index = (int) floorf(t);
        t = t - index;

        int indices[4];
        indices[0] = (index + numPoints - 1) % numPoints;
        indices[1] = (indices[0] + 1) % numPoints;
        indices[2] = (indices[1] + 1) % numPoints;
        indices[3] = (indices[2] + 1) % numPoints;

        return this->GetCatmullRomPoint(t, this->controlPoints[indices[0]], this->controlPoints[indices[1]], this->controlPoints[indices[2]], this->controlPoints[indices[3]]);
    }

    void CatmullRomAnimation::GenerateCurveRendering() {
        vector<glm::vec3> vertices;

        for(float t = 0.0f; t < 1.0f; t += 0.01f) {
            auto [pos, deriv] = this->GetGlobalCatmullRomPoint(t);

            vertices.push_back(pos);
        }

        this->numCurveVertices = static_cast<int>(vertices.size());

        glGenBuffers(1, &this->curveVbo);

        glBindBuffer(GL_ARRAY_BUFFER, this->curveVbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    CatmullRomAnimation::~CatmullRomAnimation() {
        glDeleteBuffers(1, &this->curveVbo);
    }
}
