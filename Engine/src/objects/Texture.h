#ifndef CG_TP_ENGINE_SRC_OBJECTS_TEXTURE_H_
#define CG_TP_ENGINE_SRC_OBJECTS_TEXTURE_H_

#include <iostream>

#include <glad/glad.h>

#include "ObjectCache.h"

namespace engine::objects {
    class Texture {
    private:
        static ObjectCache<Texture> cache;

        std::string filename;
        GLuint textureId;

    public:
        Texture(const std::string& filename);

        Texture(const Texture& texture) = delete;
        Texture& operator=(const Texture& other) = delete;

        ~Texture();

        inline void Bind() const {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, this->textureId);
        }

        inline void Unbind() const {
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
        }

        static ObjectCache<Texture>& GetCache() {
            return cache;
        }
    };
}

#endif //CG_TP_ENGINE_SRC_OBJECTS_TEXTURE_H_
