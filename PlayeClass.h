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
		position = glm::vec3(0.0f, 0.0f, 0.0f);
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		speed = 0.5f;
		jump_speed = 1.5f;
	}

	void FarAway()
	{
		if (glm::abs(position.x) > 17.0f || glm::abs(position.z) > 45.0f) color = glm::vec3(1.0f, 0.0f, 0.0f);
		else
		{
			color = glm::vec3(0.0f, 0.0f, 1.0f);
		}
	}

	void Move(glm::vec3 change)
	{
		position = position + speed * change;
	}

	void EnemyMove(float speed)
	{
		position.z -= speed;
	}

	bool CheckCollision(const Player& enemy) {
		glm::vec3 distance = glm::abs(this->position - enemy.position);
		return (distance.x <= 0.5f) && (distance.y <= 0.5f) && (distance.z <= 0.5f);
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
};