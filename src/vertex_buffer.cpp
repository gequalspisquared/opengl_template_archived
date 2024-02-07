#include <vector>

#include <glad/glad.h>

#include "vertex_buffer.h"

VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &m_id);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::set_data(const float* vertices, unsigned int size_bytes) const {
    bind();
    glBufferData(GL_ARRAY_BUFFER, size_bytes, vertices, GL_STATIC_DRAW);
}

void VertexBuffer::set_data(const std::vector<float>& vertices) const {
    set_data(vertices.data(), vertices.size() * sizeof(float));
}

void VertexBuffer::set_attributes(unsigned int index, 
                                  unsigned int size, 
                                  unsigned int stride, 
                                  unsigned int offset) const {
    // static unsigned int attribute_num = 0;

    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
    // attribute_num++;
}