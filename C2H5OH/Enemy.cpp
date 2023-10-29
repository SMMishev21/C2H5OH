#include "Enemy.hpp"

void Enemy::aiMove(Player* plr, Clock& iFrames, Time& dt, std::vector<Enemy*>& enemies, bool& dash) {

}

void Enemy::takeDamage(float damage) {
	this->hp -= damage;
}

float Enemy::getHp() {
	return this->hp;
}