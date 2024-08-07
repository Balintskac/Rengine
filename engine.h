#pragma once

#include "param.hpp"
#include "shader.hpp"

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "camera.hpp"
#include "mesh.h"

using namespace std;

class Engine {

private: 
	GLFWwindow* window = nullptr;
public:
	Camera camera;

	//vector<unique_ptr<Cube>> objects;

	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;
	//static float fov;


	// timing
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	static Engine& get() {
		if (nullptr == instance)
			instance = new Engine;
		return *instance;
	}
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
	static void destruct() {
		delete instance;
		instance = nullptr;
	}

	void processInput(GLFWwindow* window);
	void renderLoop();
	void render(vector<unique_ptr<Mesh>>& meshes);
	void createcontext();
	// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
	{
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

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

private:
	Engine() = default;
	~Engine() = default;
	static Engine* instance;
};