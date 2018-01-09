#version 330 

in vec4 clipSpace;
in vec2 textureCoords;
in vec3 toCameraVector;

out vec4 FragColor;

uniform sampler2D reflecTexture;
uniform sampler2D refracTexture;
uniform sampler2D dudvMap;
uniform sampler2D normalMap;
uniform vec3 lighColor;

uniform float moveFactor;

const float waveStrength = 0.007;

void main()
{
    
    vec2 ndc = (clipSpace.xy / clipSpace.w) / 2.0 + 0.5;
    vec2 refracTexCoord = vec2(ndc.x, ndc.y);
    vec2 reflecTexCoord = vec2(ndc.x, -ndc.y);

	vec2 distortedTexCoords = texture(dudvMap, vec2(textureCoords.x + moveFactor, textureCoords.y)).rg * 0.1;
	distortedTexCoords = textureCoords + vec2(distortedTexCoords.x, distortedTexCoords.y + moveFactor);
	vec2 finalDistortion = (texture(dudvMap, distortedTexCoords).rg * 2.0 - 1.0) * waveStrength;

    refracTexCoord += finalDistortion;
    refracTexCoord = clamp(refracTexCoord, 0.001, 0.999);

    reflecTexCoord += finalDistortion; 
    reflecTexCoord.x = clamp(reflecTexCoord.x, 0.001, 0.999);
    reflecTexCoord.y = clamp(reflecTexCoord.y, -0.999, -0.001);
    
    vec4 refracColor = texture(refracTexture, refracTexCoord);
    vec4 reflecColor = texture(reflecTexture, reflecTexCoord);


    //FragColor = mix(reflecColor, refracColor, 0.5);

    
    //FRESNEL EFFECT
    vec3 viewVector = normalize(toCameraVector);
    float refractiveFactor = dot(viewVector, vec3(0.0, 1.0, 0.0));
    refractiveFactor = pow(refractiveFactor, 1.0);

    vec4 normalMapColor = texture(normalMap, distortedTexCoords);
    vec3 normal = vec3(normalMapColor.r * 2.0 - 1, normalMapColor.b, normalMapColor.g * 2.0 -1.0);
    normal = normalize(normal);

    FragColor = mix(reflecColor, refracColor, refractiveFactor);
    //add blue color to water
    //FragColor = mix(FragColor, vec4 (0.0, 0.3, 0.5, 1.0), 0.2);
    //FragColor = normalMapColor;
}