#version 330 

uniform sampler2D gSampler[5]; 
uniform sampler2D shadowMap; 

uniform vec4 vColor; 
 
uniform float fRenderHeight; 
uniform float fMaxTextureU; 
uniform float fMaxTextureV;

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;

void main()
{
    //outColor = vec4(0 , 255, 0, 1.0f);
    FragColor = texture(texture1, TexCoord);
}