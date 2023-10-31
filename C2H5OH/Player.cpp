#include "Player.hpp"


void Player::setPlayerInfo(int health, float speed) {
	this->health = health;
	this->speed = speed;
}

void Player::takeDamage(int damage) {
	this->health -= damage;
}