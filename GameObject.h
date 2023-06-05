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
	vec3 scale;

public:
	GameObject(vec3 pos, vec4 col, vec3 scal);
	GameObject(GameObject& A);
	inline vec3 getPos() const { return position; }
	inline vec4 getColor() { return color; }
	inline vec3 getScale() { return scale; }
	inline vec3& getRefPos() { return position; }
	inline void setPos(vec3 pos) { position = pos; }
	inline void setColor(vec4 col) { color = col; }

};

