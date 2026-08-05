#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    //Complete Inversion PostProcessing
    FragColor = vec4(1-vec3(texture(screenTexture, TexCoords)),1.0);

    /*
    //Color Component Only Inversion PostProcessing
    vec3 texColor = vec3(texture(screenTexture, TexCoords));
    FragColor = vec4(1-texColor.x, texColor.y, texColor.z ,1.0);
    */

    /*
    //Regular Texture
    FragColor = texture(screenTexture, TexCoords);
    */
}