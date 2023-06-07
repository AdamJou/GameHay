   #include "BoxCollider.h"

   glm::vec3 BoxCollider::Intersects(const BoxCollider& other) const {
    // Check for intersection on the x, y, and z axes
       if(!other.isActive) 
           return glm::vec3(0.0f, 0.0f, 0.0f);
    if ((minExtents.x <= other.maxExtents.x && maxExtents.x >= other.minExtents.x) &&
        (minExtents.y <= other.maxExtents.y && maxExtents.y >= other.minExtents.y) &&
        (minExtents.z <= other.maxExtents.z && maxExtents.z >= other.minExtents.z))
    {
        // Compute the difference vector between the center of both boxes
        glm::vec3 difference = getPos() - other.getPos();

        // Determine from which side the other box is colliding
        if (std::abs(difference.x) > std::abs(difference.y)) {
            if (difference.x > 0)
                return glm::vec3(1.0f, 0.0f, 0.0f);  // Collision from right
            else
                return glm::vec3(-1.0f, 0.0f, 0.0f);  // Collision from left
        } else {
            if (difference.y > 0)
                return glm::vec3(0.0f, 1.0f, 0.0f);  // Collision from top
            else
                return glm::vec3(0.0f, -1.0f, 0.0f);  // Collision from bottom
        }
    }

    // No intersection
    return glm::vec3(0.0f, 0.0f, 0.0f);
}