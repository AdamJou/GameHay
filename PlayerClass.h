#pragma once
#include "BoxCollider.h"
#include <vector>


class PlayerClass : public BoxCollider
{
public:
    glm::vec3 velocity;
    glm::vec3 gravity = glm::vec3(0.0f, -9.8f, 0.0f);

    bool isJumping = false;
    float jumpSpeed = 10.0f;
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
        if (isJumping) {
            // add the jump speed to the player's velocity
            velocity.y += jumpSpeed * dt;
        }

        // apply gravity to the player's velocity
        velocity += gravity * dt;

        // update the player's position
        this->getRefPos() += velocity * dt;

        // if the player is below the ground
        if (normal.y > 0.0f) {
            // stop the player from falling further
            this->getRefPos().y = 0.3f;
            velocity.y = 0.0f;

            // the player is no longer jumping
            isJumping = false;
        }
    }
        // function to make the player jump
        void jump() {
            if (!isJumping) {
                // the player is now jumping
                isJumping = true;

                // add the jump speed to the player's velocity
                velocity.y += jumpSpeed;
            }
        }
    
};


