#include "GameObject.h"
GameObject::GameObject(vec3 pos, vec4 col, float* vert, float* indi) : position(pos), color(col)
{
	vertices = vert;
	indices = indi;
}