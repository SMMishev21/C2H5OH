#pragma once
#include "precompile.hpp"
#include "RenderObject.hpp"
#include "EllipseHitbox.hpp"
#include "RectangleHitbox.hpp"
#include <unordered_map>

class Player : public RenderObject {
private:
public:
	
	EllipseHitbox* hitbox;
	EllipseHitbox* collisionHitbox;

	void init(Texture& texture, Vector2f position, char type) override;
	void setPlayerInfo(int health, float speed);
	void takeDamage(int damage);
	void move(Vector2f offset) override;
	void setPosition(Vector2f newPosition) override;
	int health{ 100 };
	float speed;
	Vector2f velocity;
	std::unordered_map<std::string, int> inventory;
};
