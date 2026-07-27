//
// Created by Jules BRISARD on 27/07/2026.
//

#ifndef OPENGL_MESH_H
#define OPENGL_MESH_H
#include <vector>

#include "shader.h"
#include <string>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
};

class Mesh {
    public:
        // mesh data
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, const std::vector<Texture> &textures)
        {
            this->vertices = vertices;
            this->indices = indices;
            this->textures = textures;

            setupMesh();
        }

    void Draw(const Shader &shader)
        {
            unsigned int diffuseNr = 1;
            unsigned int specularNr = 1;
            for(unsigned int i = 0; i < textures.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
                // retrieve texture number (the N in diffuse_textureN)
                std::string number;
                std::string name = textures[i].type;
                if(name == "texture_diffuse")
                    number = std::to_string(diffuseNr++);//Post incrementation
                else if(name == "texture_specular")
                    number = std::to_string(specularNr++);

                //Set the right value to the corresponding uniform sampler2D
                shader.setInt(("material." + name + number).c_str(), i);
                glBindTexture(GL_TEXTURE_2D, textures[i].id);
            }
            glActiveTexture(GL_TEXTURE0);

            // draw mesh
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    private:
        //  render data
        unsigned int VAO, VBO, EBO;

    void setupMesh()
    {
        glGenVertexArrays(1, &VAO);//Generate a Vertex Array Object
        glGenBuffers(1, &VBO);//Generate a Vertex Buffer Object, storing vertices and all their properties
        glGenBuffers(1, &EBO);//Generate an Element Buffer Objet, storing vertices indexes

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        //Structs properties and array elements are both sequential in memory,
        //so we pass the address of the first property of the first array element and all the properties of all
        //the array elements will be sequential in the buffer
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                     &indices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        // vertex texture coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        glBindVertexArray(0);
    }
};

#endif //OPENGL_MESH_H
