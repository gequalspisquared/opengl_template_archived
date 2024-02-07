#include <glad/glad.h>

#include "VertexArray.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_id);
}

void VertexArray::bind() const {
    glBindVertexArray(m_id);
}