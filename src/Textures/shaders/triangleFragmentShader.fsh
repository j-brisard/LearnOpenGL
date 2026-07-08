#version 330 core
in vec3 vertexColor;
out vec4 FragColor;
uniform float brightness;

void main()
{
    FragColor = vec4(vertexColor*brightness, 1.0);
}
