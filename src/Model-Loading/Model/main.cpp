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
#include <string>

#include "model.h"

//Directional Light
glm::vec3 lightDirection = glm::vec3(0.0f, 0.0f, -1.0f);

//Point Lights
glm::vec3 pointLightPositions[] = {
    glm::vec3( 1.5f,  0.2f,  1.0f),
    glm::vec3( 2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3( 0.0f,  0.0f, -3.0f)
};

float screen_width = 800;
float screen_height = 600;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame
float currentFrame = 0.0f;

//Last X and Y cursor coordinates
float lastX = screen_width/2, lastY = screen_height/2;

//Used to determine the first time the mouseCallback is called
bool firstMouse = true;

//Camera initialization
auto camera = Camera(glm::vec3(0.0f, 0.0f, 1.0f));

void init_cube(Shader& shader, const char* vertexPath, const char* fragmentPath, unsigned int& new_VAO) {

    Shader new_shader(vertexPath,fragmentPath);

    //Vertex Array Object (VAO)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

    unsigned int VBO; //Vertex Buffer Object
    glGenBuffers(1, &VBO); //Generates a buffer and saves its id
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind the VBO to GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Store the vertex data in GPU memory

    //Linking Vertex Attributes
    //Vertex coordinates on index 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    shader = new_shader;
    new_VAO = VAO;
}

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

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(screen_width, screen_height, "LearnOpenGL", NULL, NULL);
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

    //Model Init
    Shader modelShader("src/Model-Loading/Model/shaders/vertexShader.vsh","src/Model-Loading/Model/shaders/modelFragmentShader.fsh");
    Model backpack("resources/models/backpack/backpack.obj");

    //Light cube init
    unsigned int cube2VAO;
    Shader cube2Shader;
    init_cube(cube2Shader, "src/Lighting/Multiple-Lights/shaders/vertexShader.vsh",
              "src/Lighting/Multiple-Lights/shaders/lightSourceFragmentShader.fsh", cube2VAO);

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
        modelShader.use();

        //Set light properties
        glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

        glm::vec3 diffuseColor = lightColor   * glm::vec3(0.9f);
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.05f);

        //Point Lights
        //Light Attenuation Constants setup
        for (int i = 0; i < sizeof(pointLightPositions)/sizeof(glm::vec3); i++) {
            modelShader.setVec3("pointLights[" + std::to_string(i) + "].position",pointLightPositions[i]);
            modelShader.setFloat("pointLights[" + std::to_string(i) + "].constant",  1.0f);
            modelShader.setFloat("pointLights[" + std::to_string(i) + "].linear",    0.35f);
            modelShader.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.44f);

            modelShader.setVec3("pointLights[" + std::to_string(i) + "].ambient", ambientColor);
            modelShader.setVec3("pointLights[" + std::to_string(i) + "].diffuse", diffuseColor);
            modelShader.setVec3("pointLights[" + std::to_string(i) + "].specular", lightColor);

        }

        //Spotlight
        modelShader.setVec3("spotLight.position", camera.Position);
        modelShader.setVec3("spotLight.direction", camera.Front);
        modelShader.setFloat("spotLight.innerAngle", 5.0f);
        modelShader.setFloat("spotLight.outerAngle", 10.0f);

        modelShader.setVec3("spotLight.ambient", ambientColor);
        modelShader.setVec3("spotLight.diffuse", diffuseColor);
        modelShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);

        modelShader.setFloat("spotLight.constant",  1.0f);
        modelShader.setFloat("spotLight.linear",    0.045f);
        modelShader.setFloat("spotLight.quadratic", 0.0075f);

        modelShader.setFloat("material.shininess", 32.0f);

        modelShader.setVec3("cameraPosition", camera.Position);

        //View Matrix
        glm::mat4 view = camera.GetViewMatrix();

        int viewLoc = glGetUniformLocation(modelShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        //Projection Matrix
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(camera.Zoom), screen_width / screen_height, 0.1f, 50.0f);
        int projectionLoc = glGetUniformLocation(modelShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        //Model Matrix
        glm::mat4 model = glm::mat4(1.0f);
        int modelLoc = glGetUniformLocation(modelShader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        //Draw the cube
        backpack.Draw(modelShader);

        //LIGHT SOURCE
        cube2Shader.use();
        //View Matrix

        viewLoc = glGetUniformLocation(cube2Shader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        //Projection Matrix
        projectionLoc = glGetUniformLocation(cube2Shader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        //Visible light cube color
        cube2Shader.setVec3("lightColor",lightColor);

        //Transformations
        for (int i = 0; i < sizeof(pointLightPositions)/sizeof(glm::vec3); i++) {
            //Model Matrix
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.5f));
            int modelLoc = glGetUniformLocation(cube2Shader.ID, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

            //Draw the cube
            glBindVertexArray(cube2VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        //Unbind the Vertex Array Object after usage
        glBindVertexArray(0);


        // check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}