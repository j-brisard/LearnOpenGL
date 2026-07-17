#version 330 core
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosView - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float ambient_strengh = 0.1;
    vec3 ambient = lightColor*ambient_strengh;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir,reflectDir),0),32);
    vec3 specular = spec * lightColor * specularStrength;

    vec3 result = (specular + ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}