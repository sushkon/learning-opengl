//
//  main.cpp
//  OpenGLHelloWorld
//
//  Created by Sushant Kondguli on 3/6/20.
//  Copyright © 2020 learning. All rights reserved.
//

#include <iostream>
#include "graphics.h"
#include "math.h"
#include "shaders.h"
#include "shader.h"

int main(int argc, const char * argv[]) {
    
    // initialize the library
    if ( !glfwInit() ) {
        printf ("GLFW initialization failed\n");
        glfwTerminate();
        return -1;
    }
    
    // Setup GLFW window properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core profile = No Backwards Compatibilty
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to compilation on OS X
#endif
    
    GLFWwindow *mainWindow;
    // create a window based on its opengl context
    mainWindow = glfwCreateWindow (WIDTH, HEIGHT, "Hello World", NULL, NULL);
    if (!mainWindow) {
        printf ("GLFW window not created\n");
        glfwTerminate();
        return -1;
    }
    
    // get the buffer size informations
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
    
    // set context for GLFW to use
    glfwMakeContextCurrent (mainWindow);
    
    //  allow modern extension features
    glewExperimental = GL_TRUE;
    
    if (glewInit() != GLEW_OK) {
        printf("could not initialize glew\n");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return -1;
    }
    
    // setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);
    
    CreateTriangle();
    // build and compile our shader program
    // ------------------------------------
    Shader tShader("triangle.vs", "triangle.fs"); // you can name your shader files however you like
    unsigned int texture0 = LoadTexture("container.jpg", GL_RGB, GL_CLAMP_TO_EDGE, GL_LINEAR);
    unsigned int texture1 = LoadTexture("awesomeface.png", GL_RGBA, GL_REPEAT, GL_LINEAR);
    
    // CompileShaders();
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // loop until window closed
    
    while (!glfwWindowShouldClose (mainWindow)) {
        // get and handle user input events
        glfwPollEvents();
        
        // clear window
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        float redValue = (sin(timeValue) / 2.0f) + 0.5f;
        float delta_x  = (sin(timeValue) / 2.0f);
        float tex_ratio= (sin(timeValue) / 2.0f) + 0.5f;
        
        // render the OpenGL, put all your OpenGL code here
        // glUseProgram(shader[0]);
        // bind and activate textures
        glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture0);
        glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture1);
        tShader.use();
            // tShader.setFloat4("userColor", 1.0f, greenValue, 1.0f, 1.0);
            tShader.setFloat4("userColor", redValue, 1.0f, 1.0f, 1.0);
            tShader.setInt("texture1", 0);
            tShader.setInt("texture2", 1);
            tShader.setFloat("x_loc", delta_x);
            tShader.setFloat("textureRatio", tex_ratio);
        
        glBindVertexArray(VAO[0]);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glUseProgram(0);
        
        // swap front and back buffers
        glfwSwapBuffers(mainWindow);
        
        // pool for and process events
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
