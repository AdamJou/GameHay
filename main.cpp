#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <random>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCREEN_WIDTH = 1200;
const unsigned int SCREEN_HEIGHT = 800;

glm::vec2 move(1.0f,1.0f);
float rot_angle = glm::radians(90.0f);
bool jump_active = false;

float yPos = 0.0f;
float current_y = 0.0f;
double time_now = 0.0;
double time_current = 0.0;
float initial_velocity = 5.0f;
float gravity = -9.8f;
//Global directions 
glm::vec2 direction(0.0f);
//shaders
const char* vertexShaderSource = R"glsl(
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

const char* fragmentShaderSource = R"glsl(
#version 430 core

layout (location = 1) uniform vec4 TriangleColor;

out vec4 FragColor;
void main()
{
   FragColor = TriangleColor;
}
)glsl";
void jump() {
    time_now = glfwGetTime() - time_current;
    yPos = current_y + initial_velocity * time_now + 0.5f * gravity * time_now * time_now;

    if (yPos < 0.0f) {
        yPos = 0.0f;
        jump_active = false;
    }
}
int main()
{
    //direction = glm::normalize(glm::vec2(random_float(-1.0f, 1.0f), random_float(-1.0f, 1.0f)));
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
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);


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

    float width = 2.0f;
    float height = 0.1f;
    float depth = 2.0f;

    static const float Qube[] = {
     -width / 2, -height / 2, -depth / 2, // bottom
      width / 2, -height / 2, -depth / 2,
      width / 2,  height / 2, -depth / 2,
     -width / 2,  height / 2, -depth / 2,

     -width / 2, -height / 2,  depth / 2, // top
      width / 2, -height / 2,  depth / 2,
      width / 2,  height / 2,  depth / 2,
     -width / 2,  height / 2,  depth / 2,
    };

    unsigned int Indices[] = {
        0, 1, 2, // bottom
        2, 3, 0,
        4, 5, 6, // top
        6, 7, 4,
        0, 1, 5, // first side
        5, 4, 0,
        1, 2, 6, // second side
        6, 5, 1,
        2, 3, 7, // third side
        7, 6, 2,
        3, 0, 4, // fourth side
        4, 7, 3,
    };

    unsigned int VertexBufferId, VertexArrayId, ElementBufferId;
    glGenVertexArrays(1, &VertexArrayId);
    glGenBuffers(1, &VertexBufferId);
    glGenBuffers(1, &ElementBufferId);
    glBindVertexArray(VertexArrayId);

    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Qube), Qube, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);

    glfwSetTime(0);
    glfwSwapInterval(1);
    float shift = 2.5f; // Przesunięcie w lewo
    int gridSize = 5;
    float yPos = 0.0f;
    double lastTime = glfwGetTime();


    float cubeVertices[] = {
        // Pozycje
        -0.5f, -0.5f, -0.5f,  // Lewy-dolny-tył
        -0.5f, -0.5f,  0.5f,  // Lewy-dolny-przód
         0.5f, -0.5f,  0.5f,  // Prawy-dolny-przód
         0.5f, -0.5f, -0.5f,  // Prawy-dolny-tył
        -0.5f,  0.5f, -0.5f,  // Lewy-górny-tył
        -0.5f,  0.5f,  0.5f,  // Lewy-górny-przód
         0.5f,  0.5f,  0.5f,  // Prawy-górny-przód
         0.5f,  0.5f, -0.5f   // Prawy-górny-tył
    };

    unsigned int cubeIndices[] = {
        0, 1, 2,   // Pierwszy trójkąt (dolna ściana)
        0, 2, 3,   // Drugi trójkąt (dolna ściana)
        4, 5, 6,   // Trzeci trójkąt (górna ściana)
        4, 6, 7,   // Czwarty trójkąt (górna ściana)
        0, 1, 5,   // Piąty trójkąt (boczna ściana)
        0, 5, 4,   // Szósty trójkąt (boczna ściana)
        1, 2, 6,   // Siódmy trójkąt (boczna ściana)
        1, 6, 5,   // Ósmy trójkąt (boczna ściana)
        2, 3, 7,   // Dziewiąty trójkąt (boczna ściana)
        2, 7, 6,   // Dziesiąty trójkąt (boczna ściana)
        0, 3, 7,   // Jedenasty trójkąt (boczna ściana)
        0, 7, 4    // Dwunasty trójkąt (boczna ściana)
    };

    // Tworzenie buforów
    unsigned int cubeVBO, cubeEBO;
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    // Przypisywanie danych do buforów
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);









    //game loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VertexArrayId);

        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;
        processInput(window);

        // Macierz rzutowania
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(45.0f), static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT), 0.01f, 100.0f);
        glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(ProjMatrix));

        // Macierz widoku
        float cameraHeight = 20.0f;  // Wysokość kamery
        float cameraDistance = 10.0f; // Odległość kamery od planszy
        glm::vec3 cameraPosition(shift * (gridSize - 1) / 2.0f, cameraHeight, -cameraDistance); // Pozycja kamery z podwyższoną wysokością i odległością
        glm::vec3 centerOfGrid(shift * (gridSize - 1) / 2.0f, 0.0f, shift * (gridSize - 1) / 2.0f); // Środek planszy
        glm::vec3 upDirection(0.0f, 1.0f, 0.0f); // Kierunek góry wzdłuż osi Y
        glm::mat4 ViewMatrix = glm::lookAt(cameraPosition, centerOfGrid, upDirection); // Patrzenie na planszę od góry
        glUniformMatrix4fv(3, 1, GL_FALSE, glm::value_ptr(ViewMatrix));
        glUniformMatrix4fv(4, 1, GL_FALSE, glm::value_ptr(glm::mat4(0.0f)));



    

        // Sześciany
        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                // Obliczanie przesunięcia dla każdej kostki
                float xPos = i * shift;
                float zPos = j * shift;

                // Obliczanie unikalnego koloru dla każdej kostki
                float r = static_cast<float>(i) / gridSize;
                float g = static_cast<float>(j) / gridSize;
                float b = 1.0f - r - g;

                // ModelMatrix dla każdej kostki
                glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(xPos, yPos, zPos));
                ModelMatrix = glm::rotate(ModelMatrix, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
                glUniformMatrix4fv(4, 1, GL_FALSE, glm::value_ptr(ModelMatrix));

                glUniform4f(1, r, g, b, 1.0f); // Unikalny kolor dla każdej kostki
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                
            }
        }



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VertexArrayId);
    glDeleteBuffers(1, &VertexBufferId);
    glDeleteBuffers(1, &ElementBufferId);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    
    float boundary_x_min = -20.0f;
    float boundary_x_max = 20.0f;
    float boundary_z_min = -2.0f;
    float boundary_z_max = 50.0f;
    float half_width = 0.5f; // Half of the rectangle's width
    float move_delta = 0.1f;
    
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        rot_angle += glm::radians(1.0f);

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        rot_angle -= glm::radians(1.0f);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        move.x += move_delta * cos(rot_angle);
        move.y += move_delta * sin(rot_angle);
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        move.x -= move_delta * cos(rot_angle);
        move.y -= move_delta * sin(rot_angle);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        if (!jump_active)
        {
            jump_active = true;
            time_current = glfwGetTime();
            current_y = yPos;
        }
    }
    if (move.x - half_width <= boundary_x_min || move.x + half_width >= boundary_x_max) {
        rot_angle = glm::pi<float>() - rot_angle;
    }

    if (move.y - half_width <= boundary_z_min || move.y + half_width >= boundary_z_max) {
        rot_angle = -rot_angle;
    }
    
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}