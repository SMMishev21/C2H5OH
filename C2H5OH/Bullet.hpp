#pragma once
#include "RenderObject.hpp"

class Bullet : public RenderObject {
public:
	Bullet(float damage, float maxDistance, char owner);

	Vector2f direction;
	float speed;
	char owner;
	float damage{ 0 };
	float distance{ 0 };
	float maxDistance{ 0 };
};