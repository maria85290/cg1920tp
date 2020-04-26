#ifndef CG_TP_ENGINE_SRC_SCENE_ENTITIES_CATMULLROMANIMATION_H_
#define CG_TP_ENGINE_SRC_SCENE_ENTITIES_CATMULLROMANIMATION_H_

#include "Entity.h"

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glad/glad.h>

namespace engine::scene::entities {
    class CatmullRomAnimation: public Entity {
    private:
        int time;
        /** How much the t parameter increases every second. */
        float tPerSecond;

        std::vector<glm::vec3> controlPoints;

        static glm::mat4 coefficientMatrix;

        GLuint curveVbo;
        int numCurveVertices;

        float t = 0;
        glm::vec3 y = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 position;
        glm::mat4 orientation;

        const std::tuple<glm::vec3, glm::vec3> GetCatmullRomPoint(float t, const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);
        const std::tuple<glm::vec3, glm::vec3> GetGlobalCatmullRomPoint(float gt);

        void GenerateCurveRendering();
    public:
        ~CatmullRomAnimation();

        bool ParseXml(const tinyxml2::XMLNode *node) override;
        void Update(double deltaTime) override;
        void Render() const override;
    };
}

#endif //CG_TP_ENGINE_SRC_SCENE_ENTITIES_CATMULLROMANIMATION_H_
