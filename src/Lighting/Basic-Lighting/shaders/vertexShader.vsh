#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;

out vec3 Normal;
out vec3 FragPos;
out vec3 lightPosView;

void main()
{
    gl_Position = projection*view*model*vec4(aPos,1.0f);
    //Transform the normals with the "Normal Matrix", which transports the normals into world spaces while preserving
    //their meaning
    Normal = mat3(transpose(inverse(view*model))) * aNormal;
    FragPos = vec3(view*model*vec4(aPos,1.0f));
    lightPosView = vec3(view*vec4(lightPos,1.0f));

}