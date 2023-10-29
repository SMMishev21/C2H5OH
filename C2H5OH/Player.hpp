#pragma once
#include "precompile.hpp"
#include "RenderObject.hpp"

class Player : public RenderObject {
public:
	void setPlayerInfo(int health, float speed);
	int health{ 100 };
	float speed;
	Vector2f velocity;
};
