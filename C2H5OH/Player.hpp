#pragma once
#include "precompile.hpp"
#include "RenderObject.hpp"
#include <unordered_map>

class Player : public RenderObject {
public:
	void setPlayerInfo(int health, float speed);
	void takeDamage(int damage);
	int health{ 100 };
	float speed;
	Vector2f velocity;
	std::unordered_map<std::string, int> inventory;
};
