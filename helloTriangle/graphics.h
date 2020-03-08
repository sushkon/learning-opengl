//
//  graphics.h
//  OpenGLHelloWorld
//
//  Created by Sushant Kondguli on 3/8/20.
//  Copyright © 2020 learning. All rights reserved.
//

#ifndef graphics_h
#define graphics_h

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO[2], VBO[2], EBO[2], shader[2];

unsigned int LoadTexture(const char* imagePath, GLenum imageType, GLenum wrap, GLenum filter)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (data)
    {
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, imageType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture " << imagePath << std::endl;
    }
    stbi_image_free(data);
    return texture;
}

void CreateTriangle()
{
    GLfloat vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left
    };
    
    GLfloat vertices_shaders[] = {
        -0.2f, -0.2f,  0.0f,  0.4f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.2f,  0.0f,  0.0f,  1.0f, 0.2f, 0.8f, 0.0f, 0.0f,
        0.0f,  0.0f,  0.0f,  0.2f, 0.8f, 0.0f,  0.0f, 1.0f,
        0.2f, -0.2f,  0.0f,  1.0f, 0.0f, 0.8f,  1.0f, 1.0f,
        0.2f,  0.0f,  0.0f,  0.4f, 1.0f, 0.0f,  0.0f, 0.0f,
        -0.1f,  0.1f,  0.0f,  1.0f, 0.0f, 0.2f, 1.0f, 0.5f,
        0.1f,  0.1f,  0.0f,  1.0f, 0.0f, 1.0f , 0.5f, 0.5f
    };
    
    GLuint indices1[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3
    };
    
    GLuint indices1_shaders[] = {
        // 0, 1, 2,   // first triangle
        // 2, 3, 4   // second triangle
    };
    
    GLuint indices2[] = {  // note that we start from 0!
        4, 2, 6,
        5, 2, 1
    };
    
    glGenVertexArrays(1, &VAO[0]);
    glBindVertexArray(VAO[0]);
    
    glGenBuffers(1, &EBO[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);
    
    glGenBuffers(1, &VBO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    
    glGenVertexArrays(1, &VAO[1]);
    glBindVertexArray(VAO[1]);
    
    glGenBuffers(1, &EBO[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
    
    glGenBuffers(1, &VBO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

/*
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);
    
    const GLchar* theCode[1];
    theCode[0] = shaderCode;
    
    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);
    
    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);
    
    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(theShader, sizeof(eLog), NULL, eLog);
        printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
        return;
    }
    
    glAttachShader(theProgram, theShader);
}

void LinkAndValidateShader(GLuint theProgram) {
    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    
    glLinkProgram(theProgram);
    glGetProgramiv(theProgram, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(theProgram, sizeof(eLog), NULL, eLog);
        printf("Error linking program: '%s'\n", eLog);
        return;
    }
    
    glValidateProgram(theProgram);
    glGetProgramiv(theProgram, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(theProgram, sizeof(eLog), NULL, eLog);
        printf("Error validating program: '%s'\n", eLog);
        return;
    }
}

void CompileShaders() {
    shader[0] = glCreateProgram();
    if (!shader[0]) {
        printf("Error creating shader program!\n");
        return;
    }
    AddShader(shader[0], vShader, GL_VERTEX_SHADER);
    AddShader(shader[0], fShader, GL_FRAGMENT_SHADER);
    LinkAndValidateShader(shader[0]);
    
    shader[1] = glCreateProgram();
    if (!shader[1]) {
        printf("Error creating shader program!\n");
        return;
    }
    AddShader(shader[1], vShader, GL_VERTEX_SHADER);
    AddShader(shader[1], fShader2, GL_FRAGMENT_SHADER);
    LinkAndValidateShader(shader[1]);
}
*/
#endif /* graphics_h */
