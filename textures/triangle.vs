#version 330
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform float x_loc;
smooth out vec3 vecColor;
smooth out vec2 texCoord;
void main()
{
    gl_Position = vec4(pos.x + x_loc, pos.y, 0.8, 1.0);
    vecColor    = aColor;
    texCoord    = aTexCoord;
}
