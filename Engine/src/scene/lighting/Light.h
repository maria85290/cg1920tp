#ifndef CG_TP_ENGINE_SRC_SCENE_ENTITIES_LIGHT_H_
#define CG_TP_ENGINE_SRC_SCENE_ENTITIES_LIGHT_H_

#include <string>
#include <iostream>

#include <tinyxml2/tinyxml2.h>
#include <glm/vec4.hpp>

#include <glad/glad.h>
#include <stdexcept>
#include <glm/gtc/type_ptr.hpp>

namespace engine::window {
    class Window;
}

namespace engine::scene::lighting {
    /**
     * Classe genérica que representa as luzes que podem ser colocadas numa cena.
     *
     * Implementa funcionalidade comum a todas as luzes, e atribui um número de luz a cada nova
     * luz que é construida, até um máximo de 8 (por limitação do próprio OpenGL).
     */
    class Light {
    private:
        friend class ::engine::window::Window;

        static int NEXT_LIGHT_NO;

        int lightNo;

        static inline void ResetLightNo() {
            Light::NEXT_LIGHT_NO = GL_LIGHT0;
        }
    protected:
        glm::vec4 ambient;
        glm::vec4 diffuse;
        glm::vec4 specular;

        int GetLightNo() const { return lightNo; }

        Light(): lightNo(NEXT_LIGHT_NO++) {
            if(lightNo > GL_LIGHT7) {
                throw std::runtime_error("The scene contains more than 8 lights!");
            }
        }
    public:
        inline static glm::vec4 ParseLightComponent(const std::string& component, const tinyxml2::XMLElement* element) {
            return Light::ParseLightComponent(component, element, {1.0f, 1.0f, 1.0f, 1.0f});
        }

        static glm::vec4 ParseLightComponent(const std::string& component, const tinyxml2::XMLElement* element, const glm::vec4& def);

        virtual bool ParseXml(const tinyxml2::XMLNode *lightNode) = 0;

        inline virtual void Enable() const {
            glEnable(GetLightNo());
        }

        inline virtual void Disable() const {
            glDisable(GetLightNo());
        }

        /**
         * Upon destruction, the light settings are reset to OpenGL's default light settings, as described in
         * https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glLight.xml
         */
        virtual ~Light() {
            Light::Disable();

            glLightfv(GetLightNo(), GL_POSITION, glm::value_ptr(glm::vec4(0, 0, 1, 0)));
            glLightfv(GetLightNo(), GL_AMBIENT, glm::value_ptr(glm::vec4(0, 0, 0, 1)));

            switch(GetLightNo()) {
                case GL_LIGHT0:
                    glLightfv(GetLightNo(), GL_DIFFUSE, glm::value_ptr(glm::vec4(1)));
                    glLightfv(GetLightNo(), GL_SPECULAR, glm::value_ptr(glm::vec4(1)));
                    break;
                default:
                    glLightfv(GetLightNo(), GL_DIFFUSE, glm::value_ptr(glm::vec4(0)));
                    glLightfv(GetLightNo(), GL_SPECULAR, glm::value_ptr(glm::vec4(0)));
                    break;
            }

            glLightfv(GetLightNo(), GL_SPOT_DIRECTION, glm::value_ptr(glm::vec3(0, 0, -1)));
            glLightf(GetLightNo(), GL_SPOT_EXPONENT, 0);
            glLightf(GetLightNo(), GL_SPOT_CUTOFF, 180);

            glLightf(GetLightNo(), GL_CONSTANT_ATTENUATION, 1);
            glLightf(GetLightNo(), GL_LINEAR_ATTENUATION, 0);
            glLightf(GetLightNo(), GL_QUADRATIC_ATTENUATION, 0);
        }
    };
}

#endif //CG_TP_ENGINE_SRC_SCENE_ENTITIES_LIGHT_H_
