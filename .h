#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Player {
public:
	glm::vec3 position;
	glm::vec3 color;
	float speed;
	float jump_speed;
	bool jump_active;

	Player()
	{
		jump_active = false;
		position = glm::vec3(0.0f, 0.0f, -5.0f);
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		speed = 0.5f;
		jump_speed = 2.0f;
	}

	void Move(glm::vec3 change)
	{
		position = position + speed * change;
	}

	void CheckJump(float t, float g, float yPos)
	{
		if (jump_active == true)
		{
			position.y += jump_speed * t + 0.5f * g * t * t;
			if (position.y < yPos)
			{
				jump_active = false;
				position.y = yPos;
			}
		}
	}
}; #pragma once
