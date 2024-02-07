#pragma once

typedef unsigned int TextureId;

class Texture {
public:
    Texture(const char* file_path);

    void bind() const;

private:
    TextureId m_id;
};