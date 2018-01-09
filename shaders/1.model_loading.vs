#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 plane;

void main()
{
    TexCoords = aTexCoords;
    vec3 FragPos = vec3(model * vec4(aPos, 1.0));
    vec4 world_position = vec4(FragPos, 1.0);

     gl_ClipDistance[0] = dot(world_position, plane);

    vec4 position_relative_to_cam = view * world_position;
    gl_Position = projection * position_relative_to_cam;
}


