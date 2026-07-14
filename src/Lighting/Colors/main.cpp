#include <iostream>
#include <ostream>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"

glm::vec3 cube_color = glm::vec3(1.0f, 0.5f, 0.31f);
glm::vec3 light_color = glm::vec3(1.0f, 1.0f, 1.0f);

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float currentFrame = 0.0f;

//Last X and Y cursor coordinates
float lastX = 400, lastY = 300;

//Used to determine the first time the mouseCallback is called
bool firstMouse = true;

//Camera initialization
auto camera = Camera(glm::vec3(0.0f, 0.0f, 1.0f));

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
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

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float x_offset = xpos - lastX;
    float y_offset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(x_offset, y_offset, true);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void init_cube(Shader& shader, const char* vertexPath, const char* fragmentPath, unsigned int& new_VAO) {

    Shader new_shader(vertexPath,fragmentPath);

    //Vertex Array Object (VAO)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

    unsigned int VBO; //Vertex Buffer Object
    glGenBuffers(1, &VBO); //Generates a buffer and saves its id
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind the VBO to GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Store the vertex data in GPU memory

    //Linking Vertex Attributes
    //Vertex coordinates on index 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    shader = new_shader;
    new_VAO = VAO;

}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Set the function to call when resizing the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Sets the input mode to hide the cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Set the function to call when moving the mouse
    glfwSetCursorPosCallback(window, mouse_callback);

    //Set the function to call when scrolling with the mouse
    glfwSetScrollCallback(window, scroll_callback);

    //Cubes Init
    unsigned int cubeVAO;
    Shader cubeShader;
    init_cube(cubeShader, "src/Lighting/Colors/shaders/vertexShader.vsh",
              "src/Lighting/Colors/shaders/cubeFragmentShader.fsh", cubeVAO);

    unsigned int cube2VAO;
    Shader cube2Shader;
    init_cube(cube2Shader, "src/Lighting/Colors/shaders/vertexShader.vsh",
              "src/Lighting/Colors/shaders/lightSourceFragmentShader.fsh", cube2VAO);

    //OpenGL Setup
    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window))
    {
        //Update deltaTime since last frame
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //INPUT
        processInput(window); //Check for inputs and execute eventual actions

        //Buffer Clearing
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        //CUBE

        //Bind the Vertex Array Object of the cube
        glBindVertexArray(cubeVAO);
        cubeShader.use();

        const int cubeColorLoc = glGetUniformLocation(cubeShader.ID, "objectColor");
        glUniform3fv(cubeColorLoc, 1, glm::value_ptr(cube_color));

        int lightColorLoc = glGetUniformLocation(cubeShader.ID, "lightColor");
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(light_color));

        //Transformations

        //Model Matrix
        int modelLoc = glGetUniformLocation(cubeShader.ID, "model");
        glm::mat4 model = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        //View Matrix
        glm::mat4 view = camera.GetViewMatrix();

        int viewLoc = glGetUniformLocation(cubeShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        //Projection Matrix
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 50.0f);
        int projectionLoc = glGetUniformLocation(cubeShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        //Draw the cube
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //LIGHT SOURCE
        //Bind the Vertex Array Object of the lightSource
        glBindVertexArray(cube2VAO);
        cube2Shader.use();

        lightColorLoc = glGetUniformLocation(cube2Shader.ID, "lightColor");
        glUniform3fv(lightColorLoc, 1, glm::value_ptr(light_color));

        //Transformations

        //Model Matrix
        modelLoc = glGetUniformLocation(cube2Shader.ID, "model");
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        //View Matrix
        viewLoc = glGetUniformLocation(cube2Shader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        //Projection Matrix
        projectionLoc = glGetUniformLocation(cube2Shader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        //Draw the light source
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Unbind the Vertex Array Object after usage
        glBindVertexArray(0);


        // check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}