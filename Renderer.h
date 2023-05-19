#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdexcept>

#include <iostream>

#include <random>
class Renderer
{
private:
	static int instance;
	const char* vertexShaderSource;
	const char* fragmentShaderSource;
	unsigned int SCREEN_WIDTH;
	unsigned int SCREEN_HEIGHT;
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
public:
	inline Renderer(const char*,const char*);
	void createWindow(unsigned int, unsigned int);
	void initialize();

};

int Renderer::instance = 0;



