//
//  shaders.h
//  OpenGLHelloWorld
//
//  Created by Sushant Kondguli on 3/7/20.
//  Copyright © 2020 learning. All rights reserved.
//

#ifndef shaders_h
#define shaders_h

// Vertex Shader
static const char* vShader2 = "                             \n\
#version 330                                                \n\
                                                            \n\
layout (location = 0) in vec3 pos;                          \n\
layout (location = 1) in vec3 aColor;                       \n\
void main()                                                 \n\
{                                                           \n\
gl_Position = vec4(0.2+ 0.2*pos.x, 0.2*pos.y, 0.8, 1.0);    \n\
}";

// Vertex Shader
static const char* vShader = "                          \n\
#version 330                                            \n\
                                                        \n\
layout (location = 0) in vec3 pos;                      \n\
layout (location = 1) in vec3 aColor;                   \n\
uniform float x_loc;                                    \n\
smooth out vec3 vecColor;                               \n\
void main()                                             \n\
{                                                       \n\
gl_Position = vec4(pos.x + x_loc, pos.y, 0.8, 1.0);     \n\
vecColor    = aColor;                                   \n\
}";

// Fragment Shader
static const char* fShader ="                           \n\
#version 330                                            \n\
                                                        \n\
smooth in vec3 vecColor;                                \n\
out vec4 color;                                         \n\
uniform vec4 userColor;                                 \n\
void main()                                             \n\
{                                                       \n\
color = vec4(vecColor, 1.0);                            \n\
}";

// Fragment Shader
static const char* fShader2 ="                          \n\
#version 330                                            \n\
                                                        \n\
smooth in vec3 vecColor;                                \n\
out vec4 color;                                         \n\
uniform vec4 userColor;                                 \n\
void main()                                             \n\
{                                                       \n\
color = vec4(vecColor, 1.0);                            \n\
}";

#endif /* shaders_h */
