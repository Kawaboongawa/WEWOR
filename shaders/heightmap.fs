#version 330 

in vec2 TexCoord;
in vec3 worldPos;

uniform vec4 vColor; 

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float renderHeight;

void main()
{
    float scale = worldPos.y / renderHeight; 
    const float range1 = 0.45; 
    const float range2 = 0.60;
    if (scale >= 0.0 && scale < range1)
        FragColor = texture(texture1, TexCoord);
    else if (scale >= range1 && scale < range2)
    {
        scale -= range1;
        scale /= (range2 - range1);

        float scale2 = scale;
        scale = 1 - scale;
        FragColor = vec4(0.0);
        FragColor += texture(texture1, TexCoord) * scale;
        FragColor += texture(texture2, TexCoord) * scale2;
    }
    else
        FragColor = texture(texture2, TexCoord);
}