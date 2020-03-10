#version 330

smooth in vec2 texCoord;
out vec4 color;
uniform vec4 userColor;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float textureRatio;
uniform mat4 texTransform;
void main()
{
    vec4 tc = texTransform * vec4(texCoord, 0.0f, 1.0f);
    vec2 tex_coord = vec2(tc.x, tc.y);
    color = mix(texture(texture1, tex_coord), texture(texture2, (1-tex_coord)), textureRatio)  * vec4(userColor);
}
