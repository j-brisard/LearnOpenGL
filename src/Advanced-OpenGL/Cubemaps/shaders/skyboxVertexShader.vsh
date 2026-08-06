#version 330 core
layout (location = 0) in vec3 aPos;//3Dimensional position vector of the cubemap fragment

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    /*
    The fragment position vector is also the direction from origin to fragment,
    which are the Texture Coordinates the texture function (in the skyboxFragmentShader) expects with a samplerCube
    */
    TexCoords = aPos;
    gl_Position = projection * view * vec4(aPos, 1.0);
}