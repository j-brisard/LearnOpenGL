#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float brightness;

out vec3 vertexColor;

void main()
{
gl_Position = vec4((brightness-0.5)+aPos.x, -aPos.y, aPos.z, 1.0);
vertexColor = aColor;
}