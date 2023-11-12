#pragma once
#include "precompile.hpp"
#include "Enemy.hpp"

class Walker : public Enemy {
public:
    float damage{20.f};
    void aiMove(Player* plr, Clock& iFrames, float dt, std::vector<Enemy*>& enemies, bool& dash, std::vector<RenderObject*>& renderObjects, std::vector<Bullet*>& bullets)override;
};