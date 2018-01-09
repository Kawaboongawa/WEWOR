#version 330 

layout (location = 0) in vec3 inPos; 
layout (location = 1) in vec2 inTexCoord;
//layout (location = 2) in vec3 inNormal; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 cameraPosition;
uniform vec3 lightPosition;


out vec4 clipSpace;
out vec2 textureCoords;
out vec3 toCameraVector;

const float tiling = 6.0;

void main() 
{ 
  gl_ClipDistance[0] = 1;
  vec3 FragPos = vec3(model * vec4(inPos, 1.0));
  vec4 world_position = vec4(FragPos, 1.0);
  vec4 position_relative_to_cam = view * world_position;
  clipSpace = projection * position_relative_to_cam;
  gl_Position = clipSpace;
  textureCoords = vec2(inPos.x * 2.0 + 0.5, inPos.y / 2.0 + 0.5) * tiling;
  toCameraVector = cameraPosition - world_position.xyz;
}