#ifndef CG_TP_ENGINE_SRC_OBJECTS_TEXTURE_H_
#define CG_TP_ENGINE_SRC_OBJECTS_TEXTURE_H_

#include <iostream>

#include <glad/glad.h>

#include "ObjectCache.h"

namespace engine::objects {
    /**
     * Representa uma textura em memória, e implementa os métodos de carregamento
     * da textura, bem como os métodos de renderização da mesma.
     *
     * Tal como a classe \link ModelMesh, representa um recurso partilhado: texturas.
     * Deste modo, depois de um ficheiro de textura ser carregad, não precisa de voltar
     * a ser carregado novamente até a cache de texturas ter sido limpa.
     */
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
