#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"
#include <iostream>

#include <random>

int main()
{
    GameEngine::Renderer renderer;
    renderer.createWindow(1024, 1024);
   // renderer.initialize();
    getc(stdin);
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}