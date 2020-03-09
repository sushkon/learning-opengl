#version 330
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform float x_loc;
uniform float y_loc;
uniform mat4 transform;
smooth out vec3 vecColor;
smooth out vec2 texCoord;
void main()
{
    // gl_Position = transform * vec4(pos.x + x_loc, pos.y, 0.8, 1.0);
    gl_Position = transform * vec4(pos.x + x_loc, pos.y + y_loc, 1.0, 1.0);
    vecColor    = aColor;
    texCoord    = aTexCoord;
}
