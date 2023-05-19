#include "Renderer.h"

void Renderer::createWindow(int width, int height)
{
	void framebuffer_size_callback(GLFWwindow * window, int width, int height);
	void processInput(GLFWwindow * window);

	const unsigned int SCREEN_WIDTH = 1200;
	const unsigned int SCREEN_HEIGHT = 800;
}

Renderer::Renderer(
	const char* vertexShader = R"glsl(
#version 430 core

layout (location = 0) in vec3 Pos;
layout (location = 2) uniform mat4 u_ProjMatrix;
layout (location = 3) uniform mat4 u_ViewMatrix;
layout (location = 4) uniform mat4 u_ModelMatrix;

void main()
{
   gl_Position = u_ProjMatrix * u_ViewMatrix * u_ModelMatrix * vec4(Pos, 1.0);
}
)glsl",
const char* fragmentShader = R"glsl(
#version 430 core

layout (location = 1) uniform vec4 TriangleColor;

out vec4 FragColor;
void main()
{
   FragColor = TriangleColor;
}
)glsl"
) {
	if (instance > 0) throw std::logic_error("Only one instance allowed");
	instance++;
}
