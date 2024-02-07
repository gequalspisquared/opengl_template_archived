#pragma once

typedef unsigned int VertexArrayId;

class VertexArray {
public:
    VertexArray();

    void bind() const;

private:
    VertexArrayId m_id; 
};