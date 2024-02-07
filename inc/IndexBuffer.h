#pragma once

#include <vector>

typedef unsigned int IndexBufferId;

class IndexBuffer {
public:
    IndexBuffer();

    void bind() const;

    void set_data(const unsigned int* indices, unsigned int size_bytes) const;
    void set_data(const std::vector<unsigned int>& indices) const;

private:
    IndexBufferId m_id; 
};