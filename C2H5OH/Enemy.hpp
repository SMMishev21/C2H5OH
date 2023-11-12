#pragma once
#include "precompile.hpp"
#include "RenderObject.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include <semaphore>
#include <mutex>

Color ColorFromHSV(float hue, float saturation, float value);

class Enemy : public RenderObject {
protected:
    float hp{ 100 };
    RectangleShape healthBar;
    Vector2f pos;

public:
    EllipseHitbox* hitbox;
    float damage;

    virtual void init(Texture& texture, Vector2f position, char type) override;
    void move(Vector2f offset) override;
    void draw(RenderWindow& window) override;
    virtual void aiMove(Player* plr, Clock& iFrames, float dt, std::vector<Enemy*>& enemies, bool& dash, std::vector<RenderObject*>& renderObjects, std::vector<Bullet*>& bullets, std::mutex& m);
    virtual void takeDamage(float damage);
    float getHp();
};