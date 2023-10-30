#pragma once
#include "precompile.hpp"
#include "RenderObject.hpp"

class Bullet : public RenderObject {
public:
	Bullet(float damage, float maxDistance, char owner);

	Vector2f direction;
	char owner;
	float damage{ 0 };
	float distance{ 0 };
	float maxDistance{ 0 };
};