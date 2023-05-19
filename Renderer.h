#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<vector>
#include "GameObject.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>

#include <iostream>

#include <random>
namespace GameEngine {
	class Renderer
	{
	private:
		std::vector<GameObject> listOfObjects;
		//static int instance;
		const char* vertexShaderSource;
		const char* fragmentShaderSource;
		unsigned int SCREEN_WIDTH;
		unsigned int SCREEN_HEIGHT;
		unsigned int VertexBufferId, VertexArrayId, ElementBufferId;
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	public:
		Renderer(const char*, const char*);
		Renderer();
		void createWindow(unsigned int, unsigned int);
		void initialize();
		void initializeObject();

	};

	//int Renderer::instance = 0;
}
