#version 330 core

in vec2 position;
in vec3 color;

out vec3 Color;

void main()
{
    Color = vec3(0, 255, 0);
    gl_Position = vec4(position, 0.0, 1.0);
}