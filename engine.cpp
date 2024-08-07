#include "Engine.h"

#include "Model.h"
#include "plane.hpp"
#include "sky.hpp"
#include "cube.hpp"
#include "ShadowCube.h"

void Engine::createcontext() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Rengine", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
    }
  
    glfwMakeContextCurrent(window);

    // tell GLFW to capture our mouse
   // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   // Engine::fov = 45.0f;
}

void Engine::render(vector<unique_ptr<Mesh>>& meshes)
{
    {
        glm::vec3 lightPos(1.2f, 2.0f, 2.0f);
        ShadowCube shadow;
        shadow.setupMesh();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        shadow.updateShaderBindings(camera, lightPos, shadow.shadow.depthMap);
        shadow.draw();
     //   glEnable(GL_STENCIL_TEST);
      //  glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
       // glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        //  glEnable(GL_BLEND);
         // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
         Model model("C:/Users/Balintskac/source/repos/Rengine/resource/bagback");

        glDepthFunc(GL_LEQUAL);
        for (auto& mesh : meshes)
        {
           // lightPos.x = static_cast<float>(sin(glfwGetTime() * 2.0));
          //  lightPos.y = static_cast<float>(sin(glfwGetTime() * 0.7));
            //lightPos.z = static_cast<float>(sin(glfwGetTime() * 1.3));
            mesh->updateShaderBindings(camera, lightPos, shadow.shadow.depthMap);
            mesh->draw();
           // glStencilFunc(GL_ALWAYS, 1, 0xFF);
           // glStencilMask(0x00);
          //  glEnable(GL_DEPTH_TEST);
        }

        glDepthFunc(GL_LESS);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }   
}

void Engine::renderLoop()
{
    // lighting
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {   glViewport(0, 0, width, height); });
  //  glfwSetCursorPosCallback(window, mouse_callback);
 /*
    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
        Engine::fov -= (float)yoffset;
        if (Engine::fov < 1.0f)
            Engine::fov = 1.0f;
        if (Engine::fov > 45.0f)
            Engine::fov = 45.0f;
        });
        */
   //  [](GLFWwindow* window, double xoffset, double yoffset) { camera.ProcessMouseScroll(static_cast<float>(yoffset)); });
    vector<unique_ptr<Mesh>> meshes;

    // load models
    // -----------
   // Model ourModel("C:/Users/Balintskac/source/repos/Rengine/resource/model/bugatti.obj");

    meshes.emplace_back(new Cube());
    meshes.emplace_back(new Plane());
    meshes.emplace_back(new Sky());
   // meshes.emplace_back(new DepthMap());

     for (auto& mesh : meshes)
        mesh->setupMesh();

    while (!glfwWindowShouldClose(window))
    {     
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);
        render(meshes);
       //s camera.Zoom -= 0.5f;
    }
    /*
    for (auto& mesh : meshes)
    {
        delete mesh;
    }
    */

    glfwTerminate();
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Engine::processInput(GLFWwindow* window)
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