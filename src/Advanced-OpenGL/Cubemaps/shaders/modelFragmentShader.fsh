#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform samplerCube skybox;
uniform vec3 cameraPos;

void main()
{
    vec3 incident = (FragPos-cameraPos);
    vec3 reflection = reflect(incident,normalize(Normal));
    FragColor = vec4(texture(skybox, reflection).rgb*0.7, 1.0);
}