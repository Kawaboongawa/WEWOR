#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;
  
uniform vec4 plane;

void main()
{
    
    TexCoords = aPos;
    gl_ClipDistance[0] = 1;
    //gl_ClipDistance[0] = dot(vec4(aPos, 1.0), plane);
    gl_Position = projection * view * vec4(aPos, 1.0);
    
}
