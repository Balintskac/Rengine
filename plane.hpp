#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.hpp"
#include "mesh.h"
#include "texture.h"

class Plane : public Mesh {

public:

    Shader shader;

    void setupMesh() {
        shader.loadShaders("plane.vs", "plane.fs");
        float planeVertices[] = {
            // positions            // normals         // texcoords
             10.0f, -4.0f,  3.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
            -10.0f, -4.0f,  3.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
            -10.0f, -4.0f, -3.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

             10.0f, -4.0f,  3.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
            -10.0f, -4.0f, -3.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
             10.0f, -4.0f, -3.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
        };

        glewInit();
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glBindVertexArray(0);
    }

    void draw() {
        shader.use();
        Texture texture;
        unsigned int floorTexture = texture.loadTexture("C:/Users/Balintskac/source/repos/Rengine/resource/wood.png");
        glBindVertexArray(VAO);
        glDisable(GL_CULL_FACE);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glEnable(GL_CULL_FACE);
        glBindVertexArray(0);
    }

    void deleteBuffers() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    void updateShaderBindings(Camera cam, glm::vec3 lightPos, unsigned int depthMap) {
        shader.use();
        shader.setInt("floorTexture", 0);
        shader.setInt("shadowMap", 1);
        Texture texture;
        unsigned int floorTexture = texture.loadTexture("C:/Users/Balintskac/source/repos/Rengine/resource/wood.png");
        glBindVertexArray(VAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, floorTexture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthMap);

        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
        float near_plane = 1.0f, far_plane = 7.5f;
        lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;
        shader.setMat4("lightSpaceMatrix", lightSpaceMatrix);
        // shader.setInt("depthMap", 0);
        glm::mat4 projection = glm::perspective(glm::radians(cam.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = cam.GetViewMatrix();
        shader.setInt("texture1", 0);
        shader.setInt("shadowMap", 1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        // set light uniforms
        shader.setVec3("viewPos", cam.Position);
        shader.setVec3("lightPos", lightPos);
        shader.setInt("blinn", 0);
    }

};