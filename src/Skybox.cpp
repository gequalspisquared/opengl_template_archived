#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "Skybox.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

float skybox_vertices[] = {
        // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

Skybox::Skybox(const SkyboxFacePaths& paths, Shader* skybox_shader) 
    : m_shader(skybox_shader) {
    VertexBuffer VBO;
    m_vao.bind();
    VBO.bind();
    // std::cout << sizeof(skybox_vertices) << "\n";
    VBO.set_data(skybox_vertices, sizeof(skybox_vertices));
    VBO.set_attributes(0, 3, 3, 0); // position

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
    
    stbi_set_flip_vertically_on_load(false);

    int width, height, num_channels;
    for (size_t i = 0; i < paths.size(); i++) {
        unsigned char* data = stbi_load(paths[i], &width, &height, &num_channels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else {
            std::cerr << "Failed to load skybox texture at: " << paths[i] << std::endl;
        }
        stbi_image_free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // m_shader->set_int("skybox", 0);
}

void Skybox::draw() const {
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    m_shader->use();
    m_vao.bind();
    // glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
}