#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emit;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

in vec3 Normal;
in vec3 FragPos;
in vec3 lightPosView;
in vec2 TexCoords;

out vec4 FragColor;

void main()
{
    vec3 ambient = light.ambient*vec3(texture(material.diffuse, TexCoords));

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosView - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse*diff*vec3(texture(material.diffuse, TexCoords));

    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir,reflectDir),0),material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoords));

    vec3 emit = 0*vec3(texture(material.emit,TexCoords));

    vec3 result = emit + specular + ambient + diffuse;
    FragColor = vec4(result, 1.0);
}