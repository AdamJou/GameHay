#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma once
using namespace glm;

class GameObject
{
private:
	vec3 position;
	vec4 color;
	float* vertices = nullptr;
	float* indices = nullptr;
public:
	GameObject(vec3 pos, vec4 col, float* vert, float* indi);
	inline vec3 getPos() { return position; }
	inline vec4 getColor() { return color; }

};

