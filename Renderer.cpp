#include "Renderer.h"
using namespace GameEngine;

void Renderer::createWindow(unsigned int width, unsigned int height)
{
	void framebuffer_size_callback(GLFWwindow * window, int width, int height);
	void processInput(GLFWwindow * window);

	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _APPLE_
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL Przeksztalcenia", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::logic_error("tyœ?");
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw std::logic_error("tyœ?");
    }

    glEnable(GL_DEPTH_TEST);

}

void Renderer::initialize()
{
    // build and compile our shader program
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Renderer::Renderer() {
    vertexShaderSource = R"glsl(
	#version 430 core
	
	layout (location = 0) in vec3 Pos;
	layout (location = 2) uniform mat4 u_ProjMatrix;
	layout (location = 3) uniform mat4 u_ViewMatrix;
	layout (location = 4) uniform mat4 u_ModelMatrix;
	
	void main()
	{
	   gl_Position = u_ProjMatrix * u_ViewMatrix * u_ModelMatrix * vec4(Pos, 1.0);
	}
	)glsl";
    fragmentShaderSource = R"glsl(
	#version 430 core
	
	layout (location = 1) uniform vec4 TriangleColor;
	
	out vec4 FragColor;
	void main()
	{
	   FragColor = TriangleColor;
	}
	)glsl";
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
	)glsl") 
{
	//if (instance > 0) throw std::logic_error("Only one instance allowed");
	//instance++;
	vertexShaderSource = vertexShader;
	fragmentShaderSource = fragmentShader;
}



void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}