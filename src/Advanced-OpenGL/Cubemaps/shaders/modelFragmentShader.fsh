#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform samplerCube skybox;
uniform vec3 cameraPos;

void main()
{
    vec3 incident = (FragPos-cameraPos);

    //Reflection
    //vec3 r = reflect(incident,normalize(Normal));

    //Refraction
    float ratio = 1.00 / 1.52;
    vec3 r = refract(incident, normalize(Normal), ratio);

    FragColor = vec4(texture(skybox, r).rgb*0.7, 1.0);
}