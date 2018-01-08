#version 330 

in vec4 clipSpace;

out vec4 FragColor;

uniform sampler2D reflecTexture;
uniform sampler2D refracTexture;

void main()
{
    vec2 ndc = (clipSpace.xy / clipSpace.w) / 2.0 + 0.5;
    vec2 refracTexCoord = vec2(ndc.x, ndc.y);
    vec2 reflecTexCoord = vec2(ndc.x, -ndc.y);
    vec4 refracColor = texture(refracTexture, refracTexCoord);
    vec4 reflecColor = texture(reflecTexture, reflecTexCoord);

    FragColor = mix(reflecColor, refracColor, 0.5);
}