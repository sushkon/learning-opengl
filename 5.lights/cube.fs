#version 330

out vec4 color;

smooth in vec3 normal;
smooth in vec3 fragPos;
smooth in vec2 texCoord;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emmission;
    float shininess;
};
uniform Material material;

struct Light {
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

uniform float time;

uniform vec3 cameraPos;
void main()
{
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
    
    // diffuse
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
    
    // specular
    vec3 cameraDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(cameraDir, reflectDir), 0.0), material.shininess);
    vec3 materialSpecular = vec3(texture(material.specular, texCoord));
    vec3 specular = light.specular * (spec * materialSpecular);
    
    // emission
    vec3 emmission = vec3(0.0f);
    if (materialSpecular == vec3(0.0f)) {
        emmission = texture(material.emmission, texCoord + vec2(0.0,time/2)).rgb;
    }
    
    vec3 result = (ambient + diffuse + specular + emmission);
    
    color = vec4(result, 1.0);
}
