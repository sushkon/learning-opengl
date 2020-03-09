//
//  main.cpp
//  OpenGLTransformations
//
//  Created by Sushant Kondguli on 3/6/20.
//  Copyright © 2020 learning. All rights reserved.
//

#include <iostream>
#include "graphics.h"
#include "math.h"
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
    Shader tShader("/Users/sushant/Documents/OpenGLTransformations/OpenGLTransformations/triangle.vs", "/Users/sushant/Documents/OpenGLTransformations/OpenGLTransformations/triangle.fs"); // you can name your shader files however you like
    Shader tShader1("/Users/sushant/Documents/OpenGLTransformations/OpenGLTransformations/triangle.vs", "/Users/sushant/Documents/OpenGLTransformations/OpenGLTransformations/triangle.fs"); // you can name your shader files however you like
    unsigned int texture0 = LoadTexture("/Users/sushant/Documents/OpenGLTransformations/OpenGLTransformations/container.jpg", GL_RGB, GL_CLAMP_TO_EDGE, GL_LINEAR);
    unsigned int texture1 = LoadTexture("/Users/sushant/Documents/OpenGLTransformations/OpenGLTransformations/awesomeface.png", GL_RGBA, GL_REPEAT, GL_LINEAR);
    
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
        float greenValue= (sin(timeValue) / 2.0f) + 0.5f;
        float redValue = (sin(timeValue) / 2.0f)  + 0.5f;
        float delta_x  = sin(timeValue);
        float delta_y  = sin(timeValue);
        float tex_ratio= (sin(timeValue) / 2.0f) + 0.5f;
        
        // render the OpenGL, put all your OpenGL code here
        // glUseProgram(shader[0]);
        // bind and activate textures
        glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture0);
        glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture1);
        
        // bind geometry
        glBindVertexArray(VAO[0]);
        
        // shader
        tShader.use();
            // set shader unifrom values
            tShader.setFloat4("userColor", 1.0f, greenValue, 1.0f, 1.0);
            tShader.setFloat4("userColor", redValue, 1.0f, 1.0f, 1.0);
            tShader.setFloat("x_loc", 0);
            tShader.setFloat("y_loc", 0);
            tShader.setFloat("textureRatio", tex_ratio);
            tShader.setInt("texture1", 0);
            tShader.setInt("texture2", 1);
        
        for (int i=0; i < 4; ++i) {
            // transform poistions
            GLfloat trans_x = -1.0f;
            if (i%2 == 0) trans_x = 1.0f;
            GLfloat trans_y = -1.0f;
            if (i > 1) trans_y = 1.0f;
            trans_x *= 0.5;
            trans_y *= 0.5;
            glm::mat4 trans = glm::mat4(1.0f);
            trans = glm::translate(trans, glm::vec3(trans_x, trans_y, 0.0f));
            trans = glm::scale(trans, glm::vec3(0.25, 0.25, 0.25));
            tShader1.setMat4("transform", trans);
            // transform textures
            glm::mat4 texTrans = glm::mat4(1.0f);
            texTrans = glm::scale(texTrans, glm::vec3(0.5, 0.5, 0.5));
            if (i==0) {
                tShader.setFloat("textureRatio", 1.0f);
            }
            if (i==1) {
                texTrans = glm::rotate(texTrans, 2*(float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
            }
            if (i==2) {
                texTrans = glm::scale(texTrans, sin((float)glfwGetTime())* glm::vec3(1.0, 1.0, 1.0));
            }
            if (i==3) {
                texTrans = glm::translate(texTrans, (float)glfwGetTime()*glm::vec3(1.0, 1.0, 0.0));
            }
            tShader.setMat4("texTransform", texTrans);
            // draw
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            
            tShader.setFloat("textureRatio", tex_ratio);
            // transform textures
            texTrans = glm::mat4(1.0f);
            texTrans = glm::rotate(texTrans, 2*(float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
            tShader.setMat4("texTransform", texTrans);
            // transform poistions
            trans_x = (0.5f * (int)(i/2));
            trans_y = (0.5f * (int)(i%2));
            trans = glm::mat4(1.0f);
            trans = glm::translate(trans, glm::vec3(trans_x-0.25, trans_y-0.25, 0.0f));
            trans = glm::scale(trans, glm::vec3(0.25, 0.25, 1));
            trans = glm::rotate(trans, (i+1)*(float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
            tShader.setMat4("transform", trans);
                // draw
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        
        glUseProgram(0);
        
        // swap front and back buffers
        glfwSwapBuffers(mainWindow);
        
        // pool for and process events
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
