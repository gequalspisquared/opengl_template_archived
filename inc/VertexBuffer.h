#pragma once

#include <vector>

typedef unsigned int VertexBufferId;

class VertexBuffer {
public:
    VertexBuffer();

    void bind() const;

    void set_data(const float* vertices, unsigned int size_bytes) const;
    void set_data(const std::vector<float>& vertices) const;
    void set_attributes(unsigned int index, unsigned int size, unsigned int stride, unsigned int offset) const;

private:
    VertexBufferId m_id; 
};