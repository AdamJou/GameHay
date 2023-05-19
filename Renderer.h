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

public:
	inline Renderer(const char*,const char*);
	void createWindow(int width, int height);

};

int Renderer::instance = 0;



