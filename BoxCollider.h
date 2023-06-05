#pragma once
#include "GameObject.h"
#include <glm/glm.hpp>

class BoxCollider: public GameObject {
public:
    glm::vec3 minExtents;  // The minimum extents of the box (bottom-left corner)
    glm::vec3 maxExtents;  // The maximum extents of the box (top-right corner)

    // Constructor
    BoxCollider(GameObject A, const glm::vec3& minExtents, const glm::vec3& maxExtents)
        : GameObject(A), minExtents(minExtents), maxExtents(maxExtents) {}

    // Check if this box collides with another
        BoxCollider(GameObject& A)
        : GameObject(A) { updateCollider(); }
        BoxCollider(vec3 pos, vec4 col, vec3 scal): GameObject(pos, col, scal) {
            updateCollider();
        }

    // Function to update the size of the collider
    void updateCollider() {
        glm::vec3 position = getPos(); 
        glm::vec3 scale = getScale(); 

        // The min and max extents are calculated from the position and scale
        minExtents = position - scale / 2.0f;
        maxExtents = position + scale / 2.0f;
    }

    glm::vec3 Intersects(const BoxCollider& other) const;
};
