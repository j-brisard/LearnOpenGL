#include <iostream>
#include <ostream>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "stb_image/stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"

// Stores the mixing factor between our 2 textures
float mix_factor = 0.5f;

//Stores the position of each of our cubes
glm::vec3 cube_positions[] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(1.5f, 0.0f, 0.0f),
    glm::vec3(-1.5f, 0.0f, 0.0f),
};

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
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        mix_factor += 0.01f;
        if (mix_factor > 1.0f)
            mix_factor = 1.0f;
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mix_factor -= 0.01f;
        if (mix_factor < 0.0f)
            mix_factor = 0.0f;

    }
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

void init_rectangle(Shader& shader, unsigned int& new_VAO) {

    Shader new_shader("src/GettingStarted/Camera/shaders/vertexShader.vsh","src/GettingStarted/Camera/shaders/rectangleFragmentShader.fsh");

    //Vertex Array Object (VAO)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int VBO; //Vertex Buffer Object
    glGenBuffers(1, &VBO); //Generates a buffer and saves its id
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind the VBO to GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Store the vertex data in GPU memory

    //Linking Vertex Attributes
    //Vertex coordinates on index 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Texture coordinates on index 1
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

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

    //Rectangle Init
    unsigned int rectangleVAO;
    Shader rectangleShader;
    init_rectangle(rectangleShader, rectangleVAO);

    //Textures setup
    stbi_set_flip_vertically_on_load(true);
    //Texture 1
    unsigned int texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //Mipmaps are only used when minimizing/downscaling
    //Texture file reading
    int width, height, nrChannels;
    unsigned char *data = stbi_load("resources/textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    //Texture 2
    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //Mipmaps are only used when minimizing/downscaling
    //Texture file reading
    data = stbi_load("resources/textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        //RECTANGLE
        rectangleShader.use();
        rectangleShader.setInt("texture1", 0);
        rectangleShader.setInt("texture2", 1);
        rectangleShader.setFloat("mix_factor", mix_factor);

        glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1); // activate the texture unit first before binding texture
        glBindTexture(GL_TEXTURE_2D, texture2);

        //Bind the Vertex Array Object of the rectangle
        glBindVertexArray(rectangleVAO);

        //Transformations

        //View Matrix
        glm::mat4 view = camera.GetViewMatrix();

        int viewLoc = glGetUniformLocation(rectangleShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        //Projection Matrix
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 50.0f);
        int projectionLoc = glGetUniformLocation(rectangleShader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        //Model Matrix
        int modelLoc = glGetUniformLocation(rectangleShader.ID, "model");
        for (int i = 0; i < cube_positions->length(); i++) {
            glm::mat4 model = glm::mat4(1.0f);
            if (!i){
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 0.5f, 0.0f));
            }
            model = glm::translate(model,cube_positions[i]);
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            //Draw the cube
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