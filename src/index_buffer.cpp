#include <vector>

#include <glad/glad.h>

#include "index_buffer.h"

IndexBuffer::IndexBuffer() {
    glGenBuffers(1, &m_id);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::set_data(const unsigned int* vertices, unsigned int size_bytes) const {
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_bytes, vertices, GL_STATIC_DRAW);
}

void IndexBuffer::set_data(const std::vector<unsigned int>& indices) const {
    set_data(indices.data(), indices.size() * sizeof(unsigned int));
}