#include <iostream>
#include <string>

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "Texture.h"

enum FileExtension {
    JPG,
    PNG,
    UNKNOWN,
};

FileExtension get_file_extension(const char* file_path);

Texture::Texture(const char* file_path) {
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    // Default wrapping/ filtering options, need to figure out a system for 
    // changing these if the need arises
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    FileExtension file_extension = get_file_extension(file_path);
    unsigned int file_format = GL_RGB;
    if (file_extension == FileExtension::JPG) {
        file_format = GL_RGB;
    } else if (file_extension == FileExtension::PNG) {
        file_format = GL_RGBA;
    } else {
        std::cerr << "Could not determine texture file format, trying GL_RGB.\n";
    }

    int width, height, num_channels;
    unsigned char* data = stbi_load(file_path, &width, &height, &num_channels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, file_format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture at: " << file_path << std::endl;
    }
    stbi_image_free(data);
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, m_id);
}

FileExtension get_file_extension(const char* file_path) {
    const std::string path(file_path);

    size_t found = path.find_last_of('.');

    if (found == std::string::npos) {
        return FileExtension::UNKNOWN;
    }

    std::string extension = path.substr(found + 1);
    if (extension == "jpg" || extension == "JPG" ||
        extension == "jpeg" || extension == "JPEG") {
        return FileExtension::JPG;
    } else if (extension == "png" || extension == "PNG") {
        return FileExtension::PNG;
    }

    return FileExtension::UNKNOWN;
}