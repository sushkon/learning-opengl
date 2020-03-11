#version 330
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

smooth out vec3 normal;
smooth out vec3 fragPos;
smooth out vec2 texCoord;
void main()
{
    // note that we read the multiplication from right to left
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    normal = mat3(transpose(inverse(model))) * aNormal;
    fragPos= vec3(model * vec4(aPos, 1.0));
    texCoord = aTexCoord;
}
