#pragma once
#include "precompile.hpp"
#include "RenderObject.hpp"

class Player : public RenderObject {
public:
	void setPlayerInfo(int health, float speed);
	int health;
	float speed;
	Vector2f velocity;
};
