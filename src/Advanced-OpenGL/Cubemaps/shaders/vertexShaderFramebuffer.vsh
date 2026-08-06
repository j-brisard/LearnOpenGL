#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model; //Allow to move,scale, rotate the screen quad

void main()
{
    vec2 position = vec2(model * vec4(aPos,1.0));
    gl_Position = vec4(position, 0.0, 1.0);
    TexCoords = aTexCoords;
}