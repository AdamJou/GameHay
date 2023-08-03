#include "Renderer.h"
using namespace GameEngine;

unsigned int vertexBufferId;
unsigned int vertexArrayId;
unsigned int elementBufferId;


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

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hay", NULL, NULL);
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
    shaderProgram = glCreateProgram();
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
    BgColor = vec4(0.6f, 0.6f, 0.8f, 1.0f);
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
    BgColor = vec4(0.6f, 0.6f, 0.8f, 1.0f);
	//if (instance > 0) throw std::logic_error("Only one instance allowed");
	//instance++;
	vertexShaderSource = vertexShader;
	fragmentShaderSource = fragmentShader;
}



void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Renderer::initializeQube(const float* Qube, unsigned int* Indices, int qubeSize, int indicesSize) {
    glGenVertexArrays(1, &vertexArrayId);
    glGenBuffers(1, &vertexBufferId);
    glGenBuffers(1, &elementBufferId);
    glBindVertexArray(vertexArrayId);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, qubeSize * sizeof(float), Qube, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(unsigned int), Indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

    glfwSwapInterval(1);
}


void Renderer::addObject(GameObject* obj)
{
    listOfObjects.push_back(obj);
}

void Renderer::drawFrame()
{

    glClearColor(BgColor.r,BgColor.g,BgColor.b,BgColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(vertexArrayId);



    glm::mat4 ProjMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), 0.01f, 100.0f);
    glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(ProjMatrix));

    glm::mat4 ViewMatrix = glm::lookAt(camera.cameraPosition, camera.centerOfGrid, camera.upDirection); // Patrzenie na planszê od góry
    glUniformMatrix4fv(3, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
    glUniformMatrix4fv(4, 1, GL_FALSE, glm::value_ptr(glm::mat4(0.0f)));

    for (int a = 0; a < listOfObjects.size(); a++)
    {
        glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), listOfObjects[a]->getPos());
        ModelMatrix = glm::scale(ModelMatrix, listOfObjects[a]->getScale());
        glUniformMatrix4fv(4, 1, GL_FALSE, glm::value_ptr(ModelMatrix));

        glUniform4f(1, listOfObjects[a]->getColor().x, listOfObjects[a]->getColor().y, listOfObjects[a]->getColor().z, 1.0f); // Unikalny kolor dla ka¿dej kostki
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
}

GameEngine::Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &vertexArrayId);
    glDeleteBuffers(1, &vertexBufferId);
    glDeleteBuffers(1, &elementBufferId);
    glDeleteProgram(shaderProgram);
 
    glfwTerminate();
}
