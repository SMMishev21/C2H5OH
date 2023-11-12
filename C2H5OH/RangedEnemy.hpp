#pragma once

#include "precompile.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"

class RangedEnemy : public Enemy {
private:
    Clock shootTimer;
    Texture bulletTexture;
public:
    RangedEnemy();
    virtual void aiMove(Player* plr, Clock& iFrames, float dt, std::vector<Enemy*>& enemies, bool& dash, std::vector<RenderObject*>& renderObjects, std::vector<Bullet*>& bullets, std::mutex& m) override;
    virtual void shoot(Player* plr, std::vector<RenderObject*>& renderObjects, std::vector<Bullet*>& bullets, std::mutex& m);
};
