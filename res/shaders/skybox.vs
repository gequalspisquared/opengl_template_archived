#version 460 core
layout (location = 0) in vec3 position;

out vec3 tex_coords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    tex_coords = position;
    // tex_coords = vec3(position.xy, -position.z);
    gl_Position = projection * view * vec4(position, 1.0);
}  