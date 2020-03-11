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
#include "camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// Window dimensions
const GLint SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT/ 2.0f;
bool firstMouse = true;

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
    mainWindow = glfwCreateWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
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
    glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);
    glfwSetCursorPosCallback(mainWindow, mouse_callback);
    glfwSetScrollCallback(mainWindow, scroll_callback);
    
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);
    
    CreateTriangle();
    // build and compile our shader program
    // ------------------------------------
    Shader tShader("cube.vs", "cube.fs"); // you can name your shader files however you like
 
    Shader lightShader("cube.vs", "light.fs");
    
    // load textures (we now use a utility function to keep the code more organized)
    unsigned int diffuseMap = LoadTexture("container2.png", GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR);
    unsigned int specularMap = LoadTexture("container2_specular.png", GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR);
    unsigned int emmissionMap = LoadTexture("matrix.jpg", GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR);
    
    // CompileShaders();
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glEnable(GL_DEPTH_TEST);
    
    // loop until window closed
    while (!glfwWindowShouldClose (mainWindow)) {
        // get and handle user input events
        glfwPollEvents();

        // clear window
        glClearColor(0.0f, 0.2f, 0.2f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // bind geometry
        glBindVertexArray(lightVAO);
        glm::vec3 lightColor;
        lightColor.x = 1.0f + sin(glfwGetTime()) * 4.0f;
        lightColor.y = 1.0f + sin(1000.0f + glfwGetTime()) * 1.7f;
        lightColor.z = 1.0f + sin(500.0f + glfwGetTime()) * 2.3f;
        glm::vec3 ldiffuse = lightColor   * glm::vec3(0.5f);
        glm::vec3 lambient = ldiffuse * glm::vec3(0.2f);
        lightShader.use();
        lightShader.setVec3("lightColor", lightColor);
        GLfloat lx = 1.0f * sin(glfwGetTime()/1000);
        GLfloat lz = 1.0f * cos(glfwGetTime()/1000);
        glm::vec3 lightPosition(lx, -0.3f, lz);
        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        lightShader.setMat4("view", view);
        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SCREEN_WIDTH / (float) SCREEN_HEIGHT, 0.1f, 100.0f);
        lightShader.setMat4("projection", projection);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, lightPosition);
        model = glm::scale(model, glm::vec3(0.2f));
        // model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.3f, 0.5f));
        lightShader.setMat4("model", model);
            // draw
            glDrawArrays(GL_TRIANGLES, 0, 36);
        
        // bind texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, emmissionMap);
        
        // bind geometry
        glBindVertexArray(VAO[0]);
        
        // shader
        tShader.use();
        tShader.setMat4("view", view);
        tShader.setMat4("projection", projection);
        tShader.setInt("material.diffuse", 0);
        tShader.setInt("material.specular", 1);
        tShader.setInt("material.emmission", 2);
        tShader.setFloat("material.shininess", 32.0f);
        tShader.setVec3("light.position", lightPosition);
        tShader.setVec3("light.ambient", lambient);
        tShader.setVec3("light.diffuse", ldiffuse);
        tShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        tShader.setVec3("cameraPos", camera.Position);
        tShader.setFloat("time", glfwGetTime());
        
        glm::vec3 cubePosition(-0.1f, -0.1f, 0.0f);
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePosition);
        model = glm::scale(model, glm::vec3(0.8f));
        model = glm::rotate(model, glm::radians(-20.0f * (GLfloat)glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));
        tShader.setMat4("model", model);
        // draw
            glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glUseProgram(0);
        
        processInput(mainWindow);
        float currentFrame = glfwGetTime();
        deltaTime = (currentFrame - lastFrame);    // time between current frame and last frame
        float lastFrame = currentFrame;
        
        // swap front and back buffers
        glfwSwapBuffers(mainWindow);
        
        // pool for and process events
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    //return;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    
    lastX = xpos;
    lastY = ypos;
    
    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //return;
    camera.ProcessMouseScroll(yoffset);
}
