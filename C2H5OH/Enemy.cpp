#include "Enemy.hpp"

void Enemy::aiMove(Player* plr, Clock& iFrames, float dt, std::vector<Enemy*>& enemies, bool& dash, std::vector<RenderObject*>& renderObjects, std::vector<Bullet*>& bullets) {

}

void Enemy::takeDamage(float damage) {
    this->hp -= damage;
}

float Enemy::getHp() {
    return this->hp;
}