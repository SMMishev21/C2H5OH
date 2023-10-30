#pragma once
#include "precompile.hpp"
#include "RenderObject.hpp"
#include "Player.hpp"

class Enemy : public RenderObject {
protected:
	float hp{ 100 };
	Vector2f pos;

public:
	virtual void aiMove(Player* plr, Clock& iFrames, float dt, std::vector<Enemy*>& enemies, bool& dash);
	void takeDamage(float damage);
	float getHp();
};