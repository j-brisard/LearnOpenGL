#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{
    vec4 texCol = texture(texture1,TexCoords);
    if (texCol.w<0.05)
    discard;
    FragColor = texCol;
}