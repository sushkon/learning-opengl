#version 330

smooth in vec3 vecColor;
smooth in vec2 texCoord;
out vec4 color;
uniform vec4 userColor;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float textureRatio;
void main()
{
    color = mix(texture(texture1, texCoord), texture(texture2, (1-texCoord)), textureRatio) * vec4(vecColor, 1.0) * vec4(userColor);
}
