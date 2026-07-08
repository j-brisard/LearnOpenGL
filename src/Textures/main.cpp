#include <iostream>
#include <ostream>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "stb_image/stb_image.h"

// Stores the mixing factor between our 2 textures
float mix_factor = 0.5f;

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

}

void init_rectangle(Shader& shader, unsigned int& new_VAO) {

    Shader new_shader("src/Textures/shaders/vertexShader.vs","src/Textures/shaders/rectangleFragmentShader.fs");

    //Vertex Array Object (VAO)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    float vertices[] = {
        0.5f,  0.5f, 0.0f,      1.0f, 0.0f, 0.0f,       1.0f, 1.0f,  // top right
        0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,       1.0f, 0.0f,// bottom right
       -0.5f, -0.5f, 0.0f,      0.0f, 0.0f, 1.0f,       0.0f,0.0f,// bottom left
       -0.5f,  0.5f, 0.0f,      1.0f, 0.0f, 0.0f,       0.0f,1.0f// top left
   };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    unsigned int VBO; //Vertex Buffer Object
    glGenBuffers(1, &VBO); //Generates a buffer and saves its id
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //Bind the VBO to GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Store the vertex data in GPU memory

    unsigned int EBO; //Element Buffer Object
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Linking Vertex Attributes
    //Our vertex shader expects the Vertex positions on index 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

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

    //Rectange Init
    unsigned int rectangleVAO;
    Shader rectangleShader;
    init_rectangle(rectangleShader, rectangleVAO);

    //Textures setup
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

    while(!glfwWindowShouldClose(window))
    {
        //INPUT
        processInput(window); //Check for inputs and execute eventual actions

        //RENDERING
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //RECTANGLE
        rectangleShader.use();
        rectangleShader.setInt("texture1", 0);
        rectangleShader.setInt("texture2", 1);
        rectangleShader.setFloat("mix_factor", mix_factor);

        glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1); // activate the texture unit first before binding texture
        glBindTexture(GL_TEXTURE_2D, texture2);
        //Draw the rectangle
        glBindVertexArray(rectangleVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}