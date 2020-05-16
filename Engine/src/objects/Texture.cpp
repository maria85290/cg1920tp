#include <string>

#include <IL/il.h>

#include "Texture.h"

using std::string;

namespace engine::objects {
    ObjectCache<Texture> Texture::cache;

    Texture::Texture(const string& filename) {
        // First load the file from disk
        ilEnable(IL_ORIGIN_SET);
        ilOriginFunc(IL_ORIGIN_UPPER_LEFT);

        ILuint imageId = ilGenImage();

        ilBindImage(imageId);

        ilLoadImage(filename.c_str());

        ILint imageWidth = ilGetInteger(IL_IMAGE_WIDTH);
        ILint imageHeight = ilGetInteger(IL_IMAGE_HEIGHT);

        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

        ILubyte* imageData = ilGetData();

        // Upload the data to the GPU
        glGenTextures(1, &this->textureId);

        glBindTexture(GL_TEXTURE_2D, this->textureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        ilBindImage(0);
        ilDeleteImage(imageId);
        ilDisable(IL_ORIGIN_SET);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &this->textureId);
    }
}
