#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"
#include <iostream>

#include <random>
#include "BoxCollider.h"
#include "PlayerClass.h"

// Enum for colors
enum class Color {
    GREEN,
    BLUE,
    YELLOW,
    CYAN,
    MAGENTA,
    WHITE,
    BLACK,
    ORANGE,
    PURPLE,
    PINK
};

// Function to get a color from the enum
glm::vec4 getColorFromEnum(Color color) {
    switch (color) {
        case Color::GREEN:    return glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        case Color::BLUE:     return glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
        case Color::YELLOW:   return glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        case Color::CYAN:     return glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
        case Color::MAGENTA:  return glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
        case Color::WHITE:    return glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        case Color::BLACK:    return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        case Color::ORANGE:   return glm::vec4(1.0f, 0.5f, 0.0f, 1.0f);
        case Color::PURPLE:   return glm::vec4(0.5f, 0.0f, 0.5f, 1.0f);
        case Color::PINK:     return glm::vec4(1.0f, 0.5f, 0.5f, 1.0f);
    }
    // Return black if we don't recognize the color
    return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

// Function to get a random color in vec4
glm::vec4 getRandomColorVec4() {
    std::random_device rd;  // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, 10); // define the range
    Color randomColor = static_cast<Color>(distr(gen)); // generate numbers
    return getColorFromEnum(randomColor); // return color in vec4 format
}


int main()
{
    GameEngine::Renderer renderer;
    renderer.createWindow(1024, 1024);
    renderer.initialize();
    float width = 1.0f;
    float height = 1.0f;
    float depth = 1.0f;

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

    std::vector<BoxCollider*> AccessableObjects;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            BoxCollider* obj = new BoxCollider(*(new GameObject(vec3(i * 1.5f, 0.0f, j * 1.5f), getRandomColorVec4(), vec3(1.0f, 0.4f, 1.0f))));
            obj->updateCollider();
            AccessableObjects.push_back(obj);
            renderer.addObject(obj);
        }
    }
    PlayerClass* player = new PlayerClass(vec3(0, 5.0f, 0), getColorFromEnum(Color::BLUE), vec3(0.2));
   renderer.addObject(player);
    renderer.camera.cameraPosition = vec3(15.0f, 15.0f, 15.0f);
    renderer.camera.centerOfGrid = vec3(0);
    renderer.camera.upDirection = vec3(0.0f, 1.0f, 0.0f);
   
    float a = 0.0f;
    vec4 currentColor = getRandomColorVec4();
    while (!glfwWindowShouldClose(renderer.window))
    {
        player->update(0.01f, AccessableObjects);
        int qubeSize = sizeof(Qube) / sizeof(Qube[0]);
        int indicesSize = sizeof(Indices) / sizeof(Indices[0]);

        renderer.initializeQube(Qube, Indices, qubeSize, indicesSize);
        AccessableObjects[17]->setColor(getRandomColorVec4());
       // obj->setPos(vec3(a,a,a));
        renderer.drawFrame();
       // a += 0.01f;
    }

    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
