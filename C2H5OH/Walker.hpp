#pragma once
#include "precompile.hpp"
#include "Enemy.hpp"

class Walker : public Enemy {
public:
	void aiMove(Player* plr, Clock& iFrames, Time& dt, std::vector<Enemy*>& enemies, bool& dash) override;
};