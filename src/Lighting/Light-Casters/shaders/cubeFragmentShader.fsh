#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emit;
    float shininess;
};

//Directional Light
/*
struct Light {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
*/

//Point Light
/*
struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
*/

//Spotlight
struct Light {
    vec3  position;
    vec3  direction;
    float innerAngle;
    float outerAngle;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light light;
uniform vec3 cameraPosition;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

void main()
{
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient*vec3(texture(material.diffuse, TexCoords));

    vec3 norm = normalize(Normal);

    //Directional Light, Spotlight
    vec3 lightDir = normalize(-light.direction);

    //Point Light
    //vec3 lightDir = normalize(light.position-FragPos);

    vec3 viewDir = normalize(cameraPosition-FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse*diff*vec3(texture(material.diffuse, TexCoords));

    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir,reflectDir),0),material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular,TexCoords));

    vec3 emit = vec3(0);
    if(vec3(texture(material.specular,TexCoords))==vec3(0)){
        emit = 0*vec3(texture(material.emit,TexCoords));
    }

    //Spotlight
    vec3 result = emit + light.ambient * vec3(texture(material.diffuse, TexCoords));

    //If the fragment is inside the inner cone
    if(dot(viewDir, lightDir)>cos(radians(light.innerAngle))) {
        result = emit + attenuation * (specular + ambient + diffuse);
    }
            //Else, if it's between the inner cone and outer cone
    else if (dot(viewDir, lightDir)>cos(radians(light.outerAngle))){
        float theta     = dot(viewDir, lightDir);
        float epsilon   = cos(radians(light.innerAngle)) - cos(radians(light.outerAngle));
        float intensity = clamp((theta - cos(radians(light.outerAngle))) / epsilon, 0.0, 1.0);

        diffuse  *= intensity;
        specular *= intensity;

        result = emit + attenuation * (specular + ambient + diffuse);

    }

    FragColor = vec4(result, 1.0);
}