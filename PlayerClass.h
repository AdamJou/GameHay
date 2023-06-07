#pragma once
#include "BoxCollider.h"
#include <vector>
#include <iostream>
#include <GLFW/glfw3.h>


class PlayerClass : public BoxCollider
{
public:
    glm::vec3 velocity;
    glm::vec3 gravity = glm::vec3(0.0f, -9.8f, 0.0f);

    float sens = 5.0f;

    bool isOnGround = false;
    bool isJumping = false;
    float jumpSpeed = 6.0f;
    PlayerClass(vec3 pos, vec4 col, vec3 scal, glm::vec3 gravity = glm::vec3(0.0f, -9.8f, 0.0f)) : BoxCollider(pos, col, scal) {
        velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        this->gravity = gravity;
    }

    void update(float dt, std::vector<BoxCollider*> &colliders) {

        updateCollider();
        vec3 normal(0);
        for (int i = 0; i < colliders.size(); i++)
        {
            colliders[i]->updateCollider();
            vec3 buf = Intersects(*colliders[i]);
            if (buf != vec3(0))
                normal = buf;
        }

        // if the player is jumping

        // apply gravity to the player's velocity


        // if the player is below the ground
        
        if (normal.y > 0.0f && velocity.y < 0.0f) {
            // stop the player from falling further
            velocity.y = -velocity.y * 0.4;
            //this->getRefPos().y += velocity.y;
            if (glm::abs(velocity.y) < 0.001f) {
                velocity.y = -velocity.y + gravity.y * dt;
            }
            // the player is no longer jumping
            isJumping = false;
        }
        else
            velocity += gravity * dt;
        // update the player's position
        this->getRefPos() += velocity * dt;
        //std::cout << velocity.y << std::endl;
    }
        // function to make the player jump
        void jump() {
            if (!isJumping) {
                // the player is now jumping
                isJumping = true;
                isOnGround = false;

                // add the jump speed to the player's velocity
                velocity.y += jumpSpeed;
            }
        }
        void processInput(GLFWwindow* window,float dt)
        {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            {
                velocity.x -= sens * dt;
                isOnGround = false;
            }
            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            {
                velocity.x += sens * dt;
                isOnGround = false;
            }
            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            {
                velocity.z -= sens * dt;
                isOnGround = false;
            }
            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            {
                velocity.z += sens * dt;
                isOnGround = false;
            }
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            {
                jump();
            }
        }
    
};


