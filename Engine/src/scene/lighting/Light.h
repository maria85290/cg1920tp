#ifndef CG_TP_ENGINE_SRC_SCENE_ENTITIES_LIGHT_H_
#define CG_TP_ENGINE_SRC_SCENE_ENTITIES_LIGHT_H_

#include <string>
#include <iostream>

#include <tinyxml2/tinyxml2.h>
#include <glm/vec4.hpp>

#include <glad/glad.h>
#include <stdexcept>

namespace engine::window {
    class Window;
}

namespace engine::scene::lighting {
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

            std::cout << "Constructed GL_LIGHT: " << lightNo << std::endl;
        }
    public:
        inline static glm::vec4 ParseLightComponent(const std::string& component, const tinyxml2::XMLElement* element) {
            return Light::ParseLightComponent(component, element, {1.0f, 1.0f, 1.0f, 1.0f});
        }

        static glm::vec4 ParseLightComponent(const std::string& component, const tinyxml2::XMLElement* element, const glm::vec4& def);

        virtual ~Light() = default;

        virtual bool ParseXml(const tinyxml2::XMLNode *lightNode) = 0;

        inline virtual void Enable() const {
            glEnable(GetLightNo());
        }

        inline void Disable() const {
            glDisable(GetLightNo());
        }
    };
}

#endif //CG_TP_ENGINE_SRC_SCENE_ENTITIES_LIGHT_H_
