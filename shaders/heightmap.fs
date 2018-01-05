#version 330 

/*
in vec2 vTexCoord; 
in vec3 vNormal; 
in vec3 vWorldPos; 
in vec4 vEyeSpacePos; 
*/

uniform sampler2D gSampler[5]; 
uniform sampler2D shadowMap; 

uniform vec4 vColor; 
 
uniform float fRenderHeight; 
uniform float fMaxTextureU; 
uniform float fMaxTextureV; 

out vec4 outColor; 


void main()
{
    outColor = vec4(0 , 255, 0, 1.0f);
}