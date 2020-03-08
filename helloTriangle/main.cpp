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
    
    // generate geometry
    CreateTriangle();
    // link shaders
    CompileShaders();
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
        float delta_x  = (sin(timeValue) / 2.0f) + 0.5f;
        
        glUseProgram(shader[0]);
            int colorLoc0 = glGetUniformLocation(shader[0], "userColor");
            int delta_x0  = glGetUniformLocation(shader[0], "x_loc");
            glUniform4f(colorLoc0, 0.0f, greenValue, 0.0f, 1.0f);
            glUniform1f(delta_x0, delta_x);
            glBindVertexArray(VAO[0]);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                // glDrawArrays(GL_TRIANGLES, 3, 3);
            glBindVertexArray(0);
        glUseProgram(0);
        glUseProgram(shader[1]);
            int colorLoc1 = glGetUniformLocation(shader[1], "userColor");
            int delta_x1  = glGetUniformLocation(shader[1], "x_loc");
            glUniform4f(colorLoc1, redValue, 0.0f, 0.0f, 1.0f);
            glUniform1f(delta_x1, -delta_x);
            glBindVertexArray(VAO[1]);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                // glDrawArrays(GL_TRIANGLES, 15, 3);
            glBindVertexArray(0);
        glUseProgram(0);
        
        // swap front and back buffers
        glfwSwapBuffers(mainWindow);
        
        // pool for and process events
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
