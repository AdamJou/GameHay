#include "GameObject.h"
GameObject::GameObject(vec3 pos, vec4 col, vec3 scal) : position(pos), color(col), scale(scal)
{}

GameObject::GameObject(GameObject& A)
{
	position = A.getPos();
	color = A.getColor();
	scale = A.getScale();
}
