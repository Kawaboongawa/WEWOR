#version 330 

layout (location = 0) in vec3 inPos; 
//layout (location = 1) in vec2 inCoord;
//layout (location = 2) in vec3 inNormal; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

/*
out vec2 vTexCoord;
out vec3 vNormal;
out vec3 vWorldPos; 
out vec4 vEyeSpacePos;

uniform mat4 HeightmapScaleMatrix;
*/

void main() 
{ 

  vec3 FragPos = vec3(model * vec4(inPos, 1.0));
  vec4 world_position = vec4(FragPos, 1.0);
  vec4 position_relative_to_cam = view * world_position;
  gl_Position = projection * position_relative_to_cam;
  //gl_Position = vec4(inPos, 1.0);

  /*vec4 inPositionScaled = HeightmapScaleMatrix*vec4(inPosition, 1.0); 
  mat4 mMVP = matrices.projMatrix*matrices.viewMatrix*matrices.modelMatrix; 
    
  gl_Position = mMVP*inPositionScaled; 
  vEyeSpacePos = matrices.viewMatrix*matrices.modelMatrix*vec4(inPosition, 1.0); 
   
  vTexCoord = inCoord; 
   vNormal = inNormal; 
    
  vec4 vWorldPosLocal = matrices.modelMatrix*inPositionScaled; 
   vWorldPos = vWorldPosLocal.xyz; 
   */
}