#pragma once
#include "precompile.hpp"
#include "RenderObject.hpp"
#include "CircleHitbox.hpp"
#include "RectangleHitbox.hpp"
#include <unordered_map>

class Player : public RenderObject {
private:
public:
	
	RectangleHitbox rectangleHitbox;
	CircleHitbox circleHitbox;

	void setPlayerInfo(int health, float speed);
	void takeDamage(int damage);
	void move(Vector2f offset) override;
	int health{ 100 };
	float speed;
	Vector2f velocity;
	std::unordered_map<std::string, int> inventory;
};
