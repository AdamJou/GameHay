#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;
class Camera
{
public:
	vec3 cameraPosition;
	vec3 centerOfGrid;
	vec3 upDirection;
	Camera(vec3 p, vec3 g, vec3 d);
	inline Camera() : cameraPosition(0),centerOfGrid(0),upDirection(0) {}

};

